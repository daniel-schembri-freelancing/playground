#include "statemachine_template.h"

#include <iostream>

// ---------- helpers ----------

static std::string_view to_string(State s) {
    switch (s) {
        case State::NULL_STATE: return "NULL";
        case State::INIT:       return "INIT";
        case State::STATE_A:    return "STATE_A";
        case State::STATE_B:    return "STATE_B";
        case State::ERROR:      return "ERROR";
        case State::EXIT:       return "EXIT";
    }
    return "UNKNOWN";
}

// ---------- StateMachine ----------

StateMachine::StateMachine()
    : state_(State::NULL_STATE),
      next_state_(State::INIT),
      counter_(0),
      exit_condition_(false) {

    transitions_[State::INIT][Signal::NEXT_STATE] = State::STATE_A;
    transitions_[State::STATE_A][Signal::COUNTER_OVERFLOW] = State::STATE_B;
    transitions_[State::STATE_B][Signal::COUNTER_OVERFLOW] = State::EXIT;
    transitions_[State::ERROR][Signal::NEXT_STATE] = State::EXIT;
}

std::string_view StateMachine::get_state() const {
    return to_string(state_);
}

void StateMachine::enter_state() {
    if (state_ == next_state_) {
        return;
    }

    state_ = next_state_;
    std::cout << "[DEBUG] Entering state: " << to_string(state_) << "\n";

    if (state_ == State::EXIT) {
        exit_condition_ = true;
    }
}

void StateMachine::execute_state() {
    std::cout << "[DEBUG] Executing state: " << to_string(state_) << "\n";

    switch (state_) {
        case State::INIT:
            signal_ = Signal::NEXT_STATE;
            break;

        case State::STATE_A:
            if (++counter_ >= 10) {
                counter_ = 0;
                signal_ = Signal::COUNTER_OVERFLOW;
                std::cout << "[INFO ] Counter overflown in state A!\n";
            }
            break;

        case State::STATE_B:
            if (++counter_ >= 20) {
                counter_ = 0;
                signal_ = Signal::COUNTER_OVERFLOW;
                std::cout << "[INFO ] Counter overflown in state B!\n";
            }
            break;

        case State::ERROR:
            signal_ = Signal::NEXT_STATE;
            break;

        case State::EXIT:
        case State::NULL_STATE:
            break;
    }
}

void StateMachine::leave_state() {
    if (state_ == next_state_) {
        return;
    }

    std::cout << "[DEBUG] Leaving state: " << to_string(state_) << "\n";
}

void StateMachine::transition() {
    if (!signal_) {
        return;
    }

    auto row = transitions_.find(state_);
    if (row != transitions_.end()) {
        auto it = row->second.find(*signal_);
        if (it != row->second.end()) {
            next_state_ = it->second;

            std::cout << "[DEBUG] signal occurred, next_state: "
                      << to_string(next_state_) << "\n";

            if (state_ == next_state_) {
                std::cout << "[WARN ] Self transition detected\n";
            }
        } else {
            std::cout << "[WARN ] Unhandled signal in state\n";
        }
    }

    signal_.reset();
}

void StateMachine::run() {
    while (!exit_condition_) {
        enter_state();
        execute_state();
        transition();
        leave_state();
    }
}
