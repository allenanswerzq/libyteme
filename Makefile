
style:
	find src -name "*.cc" -o -name "*.h" | xargs -t -I{} clang-format -i {}
