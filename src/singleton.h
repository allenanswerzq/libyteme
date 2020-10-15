template <typename T>
class Singleton {
 public:
  // Returns the pointer to the singleton of type |T|.
  // This method is thread-safe.
  static T *get() LOCKS_EXCLUDED(mu_) {
    absl::MutexLock lock(&mu_);
    if (instance_) {
      return instance_;
    }

    if (destroyed_) {
      return nullptr;
    }
    if (instance_) {
      return instance_;
    }
    instance_ = new T();
    return instance_;
  }

  // Destroys the singleton . This method is only partially thread-safe.
  // It ensures that instance_ gets destroyed only once, and once destroyed, it
  // cannot be recreated. However, the callers of this method responsible for
  // making sure that no other threads are accessing (or plan to access) the
  // singleton any longer.
  static void Destruct() LOCKS_EXCLUDED(mu_) {
    absl::MutexLock lock(&mu_);
    T *tmp_ptr = instance_;
    instance_ = nullptr;
    delete tmp_ptr;
    destroyed_ = true;
  }

 private:
  static T *instance_ GUARDED_BY(mu_);
  static bool destroyed_ GUARDED_BY(mu_);
  static absl::Mutex mu_;
};

template <typename T>
T *Singleton<T>::instance_ = nullptr;

template <typename T>
bool Singleton<T>::destroyed_ = false;

template <typename T>
absl::Mutex Singleton<T>::mu_;
