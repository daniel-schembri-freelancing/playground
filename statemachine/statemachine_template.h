#pragma once

#include <unordered_map>
#include <optional>
#include <string_view>

// ---------- State / Signal ----------

enum class State {
    NULL_STATE,   // Sentinel state. Never use as real state
    INIT,
    STATE_A,
    STATE_B,
    ERROR,
    EXIT
};

enum class Signal {
    NEXT_STATE,
    COUNTER_OVERFLOW
};

// ---------- StateMachine ----------

class StateMachine {
public:
    StateMachine();

    std::string_view get_state() const;
    void run();

private:
    void enter_state();
    void execute_state();
    void leave_state();
    void transition();

    using TransitionRow = std::unordered_map<Signal, State>;
    using TransitionTable = std::unordered_map<State, TransitionRow>;

    State state_;
    State next_state_;
    std::optional<Signal> signal_;
    TransitionTable transitions_;

    int counter_;
    bool exit_condition_;
};
