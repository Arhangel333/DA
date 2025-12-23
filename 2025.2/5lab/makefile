# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wextra -Wno-sign-compare 
TARGET = program
TEST_DIR = tests

# Основная цель - компиляция программы
$(TARGET): fin.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) fin.cpp
pretest:
	python3 test_generator.py 5
# Запуск всех тестов с 1 по 5
test: $(TARGET) pretest
	@echo "Running tests 1-5..."
	@for i in 1 2 3 4 5; do \
		echo "=== Test $$i ==="; \
		./$(TARGET) < $(TEST_DIR)/0$$i.t > $(TEST_DIR)/0$$i.out; \
		if diff -q $(TEST_DIR)/0$$i.out $(TEST_DIR)/0$$i.a > /dev/null; then \
			echo "Test $$i: PASSED"; \
		else \
			echo "Test $$i: FAILED"; \
			echo "Expected:"; \
			cat $(TEST_DIR)/$$i.a; \
			echo "Got:"; \
			cat $(TEST_DIR)/$$i.out; \
		fi; \
		echo; \
	done

# Запуск конкретного теста
test%: $(TARGET)
	@echo "=== Test $* ==="
	@./$(TARGET) < $(TEST_DIR)/$*.t > $(TEST_DIR)/$*.out
	@if diff -q $(TEST_DIR)/$*.out $(TEST_DIR)/$*.a > /dev/null; then \
		echo "Test $*: PASSED"; \
	else \
		echo "Test $*: FAILED"; \
		echo "Expected:"; \
		cat $(TEST_DIR)/$*.a; \
		echo "Got:"; \
		cat $(TEST_DIR)/$*.out; \
	fi

# Очистка
clean:
	rm -f $(TARGET) $(TEST_DIR)/*.out
	rm tests/*.t tests/*.a
	

.PHONY: test test1 test2 test3 test4 test5 clean
