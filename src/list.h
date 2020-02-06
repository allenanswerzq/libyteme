/*
 * sort.frag.h: Common implementation of linked-list sorting
 *
 * Author:
 *   Raja R Harinath (rharinath@novell.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * (C) 2006 Novell, Inc.
 */

/*
 * This code requires a typedef named 'list_node' for the list node.  It
 * is assumed that the list type is the type of a pointer to a list
 * node, and that the node has a field named 'next' that implements to
 * the linked list.  No additional invariant is maintained (e.g. the
 * 'prev' pointer of a doubly-linked list node is _not_ updated).  Any
 * invariant would require a post-processing pass to fix matters if
 * necessary.
 */
typedef list_node *digit;

/*
 * The maximum possible depth of the merge tree
 *   = ceiling (log2 (maximum number of list nodes))
 *   = ceiling (log2 (maximum possible memory size/size of each list node))
 *   = number of bits in 'size_t' - floor (log2 (sizeof digit))
 * Also, each list in sort_info is at least 2 nodes long: we can reduce the
 * depth by 1
 */
#define FLOOR_LOG2(x)                                                 \
  (((x) >= 2) + ((x) >= 4) + ((x) >= 8) + ((x) >= 16) + ((x) >= 32) + \
   ((x) >= 64) + ((x) >= 128))
#define MAX_RANKS ((sizeof(size_t) * 8) - FLOOR_LOG2(sizeof(list_node)) - 1)

struct sort_info {
  int min_rank, n_ranks;
  GCompareFunc func;

  /* Invariant: ranks[i] == NULL || length(ranks[i]) >= 2**(i+1) */
  list_node *ranks[MAX_RANKS]; /* ~ 128 bytes on 32bit, ~ 512 bytes on 64bit */
};

static inline void init_sort_info(struct sort_info *si, GCompareFunc func) {
  si->min_rank = si->n_ranks = 0;
  si->func = func;
  /* we don't need to initialize si->ranks, since we never lookup past
   * si->n_ranks.  */
}

static inline list_node *merge_lists(list_node *first, list_node *second,
                                     GCompareFunc func) {
  /* merge the two lists */
  list_node *list = NULL;
  list_node **pos = &list;
  while (first && second) {
    if (func(first->data, second->data) > 0) {
      *pos = second;
      second = second->next;
    }
    else {
      *pos = first;
      first = first->next;
    }
    pos = &((*pos)->next);
  }
  *pos = first ? first : second;
  return list;
}

/* Pre-condition: upto <= si->n_ranks, list == NULL || length(list) == 1 */
static inline list_node *sweep_up(struct sort_info *si, list_node *list,
                                  int upto) {
  int i;
  for (i = si->min_rank; i < upto; ++i) {
    list = merge_lists(si->ranks[i], list, si->func);
    si->ranks[i] = NULL;
  }
  return list;
}

/*
 * The 'ranks' array essentially captures the recursion stack of a mergesort.
 * The merge tree is built in a bottom-up manner.  The control loop for
 * updating the 'ranks' array is analogous to incrementing a binary integer,
 * and the O(n) time for counting upto n translates to O(n) merges when
 * inserting rank-0 lists.  When we plug in the sizes of the lists involved in
 * those merges, we get the O(n log n) time for the sort.
 *
 * Inserting higher-ranked lists reduce the height of the merge tree, and also
 * eliminate a lot of redundant comparisons when merging two lists that would've
 * been part of the same run.  Adding a rank-i list is analogous to incrementing
 * a binary integer by 2**i in one operation, thus sharing a similar speedup.
 *
 * When inserting higher-ranked lists, we choose to clear out the lower ranks
 * in the interests of keeping the sort stable, but this makes analysis harder.
 * Note that clearing the lower-ranked lists is O(length(list))-- thus it
 * shouldn't affect the O(n log n) behaviour.  IOW, inserting one rank-i list
 * is equivalent to inserting 2**i rank-0 lists, thus even if we do i additional
 * merges in the clearing-out (taking at most 2**i time) we are still fine.
 */

#define stringify2(x) #x
#define stringify(x) stringify2(x)

/* Pre-condition: 2**(rank+1) <= length(list) < 2**(rank+2) (therefore:
 * length(list) >= 2) */
static inline void insert_list(struct sort_info *si, list_node *list,
                               int rank) {
  int i;

  if (rank > si->n_ranks) {
    if (rank > MAX_RANKS) {
      g_warning("Rank '%d' should not exceed " stringify(MAX_RANKS), rank);
      rank = MAX_RANKS;
    }
    list = merge_lists(sweep_up(si, NULL, si->n_ranks), list, si->func);
    for (i = si->n_ranks; i < rank; ++i) si->ranks[i] = NULL;
  }
  else {
    if (rank) list = merge_lists(sweep_up(si, NULL, rank), list, si->func);
    for (i = rank; i < si->n_ranks && si->ranks[i]; ++i) {
      list = merge_lists(si->ranks[i], list, si->func);
      si->ranks[i] = NULL;
    }
  }

  if (i == MAX_RANKS) /* Will _never_ happen: so we can just devolve into
                         quadratic ;-) */
    --i;
  if (i >= si->n_ranks) si->n_ranks = i + 1;
  si->min_rank = i;
  si->ranks[i] = list;
}

#undef stringify2
#undef stringify
#undef MAX_RANKS
#undef FLOOR_LOG2

/* A non-recursive mergesort */
static inline digit do_sort(list_node *list, GCompareFunc func) {
  struct sort_info si;

  init_sort_info(&si, func);

  while (list && list->next) {
    list_node *next = list->next;
    list_node *tail = next->next;

    if (func(list->data, next->data) > 0) {
      next->next = list;
      next = list;
      list = list->next;
    }
    next->next = NULL;

    insert_list(&si, list, 0);

    list = tail;
  }

  return sweep_up(&si, list, si.n_ranks);
}

//
// 1) Originally from: http://stackoverflow.com/a/27663998/432509
//
//  With following modifications:
//  - Use a pointer to the tail (remove 2x conditional checks, reduces
//  code-size).
//  - Avoid re-assigning empty values the size doesn't change.
//  - Corrected comments.
//
// 2) Token from: https://gist.github.com/ideasman42/5921b0edfc6aa41a9ce0/
//
void *listbase_sort_impl(struct Link *head,
                         int (*cmp)(const void *, const void *)) {
  int block_size = 1, block_count;
  do {
    /* Maintain two lists pointing to two blocks, 'l' and 'r' */
    struct Link *l = head, *r = head, **tail_p;

    head = NULL; /* Start a new list */
    tail_p = &head;

    block_count = 0;

    /* Walk through entire list in blocks of 'block_size'*/
    while (l != NULL) {
      /* Move 'r' to start of next block, measure size of 'l' list while doing
       * so */
      int l_size, r_size = block_size;

      block_count++;
      for (l_size = 0; (l_size < block_size) && (r != NULL); l_size++) {
        r = r->next;
      }

      /* Merge two list until their individual ends */
      bool l_empty = (l_size == 0);
      bool r_empty = (r_size == 0 || r == NULL);
      while (!l_empty || !r_empty) {
        struct Link *s;
        /* Using <= instead of < gives us sort stability */
        if (r_empty || (!l_empty && cmp(l, r) <= 0)) {
          s = l;
          l = l->next;
          l_size--;
          l_empty = (l_size == 0);
        }
        else {
          s = r;
          r = r->next;
          r_size--;
          r_empty = (r_size == 0) || (r == NULL);
        }

        /* Update new list */
        (*tail_p) = s;
        tail_p = &(s->next);
      }

      /* 'r' now points to next block for 'l' */
      l = r;
    }

    /* terminate new list, take care of case when input list is NULL */
    *tail_p = NULL;

    /* Lg n iterations */
    block_size <<= 1;

  } while (block_count > 1);

  return head;
}
