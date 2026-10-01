# ==== Project config ====
CXX       ?= g++
STD        = -std=c++17
WARN       = -Wall -Wextra -Wpedantic -Wconversion -Wno-sign-conversion
COMMON     = $(STD) $(WARN) -MMD -MP

SRC_DIR    = src
BUILD_DIR  = build
BIN_DIR    = bin
OUT_DIR    = out
TARGET     = $(BIN_DIR)/raytracer
IMAGE      = $(OUT_DIR)/image.ppm

# Sources
SRCS        = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC    = $(SRC_DIR)/main.cpp
OTHER_SRCS  = $(filter-out $(MAIN_SRC),$(SRCS))

MAIN_OBJ    = $(BUILD_DIR)/main.o
OTHER_OBJS  = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(OTHER_SRCS))
DEPS        = $(MAIN_OBJ:.o=.d) $(OTHER_OBJS:.o=.d)

# Default build mode: release + forgiving by default
CXXFLAGS  ?= $(COMMON) -O3

# Silence normal command echoing
MAKEFLAGS += -s

.PHONY: all release debug sanitize run clean clobber info

all: release

# ---- Build modes (still forgiving for non-main sources) ----
release: CXXFLAGS = $(COMMON) -O3
release: $(TARGET)

debug:   CXXFLAGS = $(COMMON) -O0 -g3
debug:   $(TARGET)

sanitize: CXXFLAGS = $(COMMON) -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: LDFLAGS  = -fsanitize=address,undefined
sanitize: $(TARGET)

# ---- Build rules ----
# main.o is strict so we always have a valid entry point
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Other objects are forgiving: ignore compile errors and move on
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

# Link whatever objects exist; main.o must exist (built strictly above)
$(TARGET): $(MAIN_OBJ) $(OTHER_OBJS)
	@mkdir -p $(BIN_DIR)
	@objs="$$(ls $(BUILD_DIR)/*.o 2>/dev/null)"; \
	$(CXX) $$objs -o $@ $(LDFLAGS)

# ---- Convenience ----
run: release
	@mkdir -p $(OUT_DIR)
	./$(TARGET) > $(IMAGE)
	@echo "Wrote $(IMAGE)"

clean:
	@$(RM) -r $(BUILD_DIR)

clobber: clean
	@$(RM) -r $(BIN_DIR) $(OUT_DIR)

info:
	@echo "SRCS      = $(SRCS)"
	@echo "MAIN_SRC  = $(MAIN_SRC)"
	@echo "OTHER_SRCS= $(OTHER_SRCS)"
	@echo "OBJS      = $(MAIN_OBJ) $(OTHER_OBJS)"
