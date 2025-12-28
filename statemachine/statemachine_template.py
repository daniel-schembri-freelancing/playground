# Give me code for a state machine in python that has three states: 'A', 'B', and 'C'.
# how to turn off copilot suggestions

import logging

logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
)

logger = logging.getLogger("StateMachine")

from typing import Callable, Optional
from enum import StrEnum, auto

class State(StrEnum):
    NULL = auto() # Sentinel state. IMPORTANT: Never use it as real state
    INIT = auto()
    STATE_A = auto()
    STATE_B = auto()
    ERROR = auto()
    EXIT = auto()

class Signal(StrEnum):
    NEXT_STATE = auto()     # Symbolizes empty transition
    COUNTER_OVERFLOW = auto()

class StateMachine:
    def __init__(self):
        self.state: State = State.NULL
        self.next_state: State = State.INIT
        self.logflow: Callable = self.log_statemachine_flow
        self.counter: int = 0
        self.exit_condition: bool = False

         # self.log_statemachine_flow
        self.signal: Optional[Signal] = None
        self.transitions = {
            State.INIT: {Signal.NEXT_STATE: State.STATE_A},
            State.STATE_A: {Signal.COUNTER_OVERFLOW: State.STATE_B},
            State.STATE_B: {Signal.COUNTER_OVERFLOW: State.EXIT},
            State.ERROR: {Signal.NEXT_STATE: State.EXIT},
            State.EXIT: {}
        }

    def log_statemachine_flow(self):
        print ("Log statemachine flow")


    def get_state(self) -> str:
        return self.state.value

    def _enter_state(self):
        if self.state == self.next_state: # Enter state already executed
            return
        self.state = self.next_state

        logger.debug(f"Entering state: {self.state}")
        match self.state:
            case State.INIT:
                pass
            case State.STATE_A:
                pass
            case State.STATE_B:
                pass
            case State.ERROR:
                pass
            case State.EXIT:
                pass
                self.exit_condition = True
            case _:
                logger.error(f"Enter State Error: Forgot a state: {self.state}")

    def _execute_state(self):
        logger.debug(f"Executing state: {self.state}")
        match self.state:
            case State.INIT:
                self.signal = Signal.NEXT_STATE
            case State.STATE_A:
                self.counter = self.counter + 1
                if self.counter >= 10:
                    self.counter = 0
                    self.signal = Signal.COUNTER_OVERFLOW
                    logger.info("Counter overflown in state A!")
            case State.STATE_B:
                self.counter = self.counter + 1
                if self.counter >= 20:
                    self.counter = 0
                    self.signal = Signal.COUNTER_OVERFLOW
                    logger.info("Counter overflown in state B!")
            case State.ERROR:
                self.signal = Signal.NEXT_STATE
            case State.EXIT:
                pass
            case _:
                logger.error(f"Execute State Error: Forgot a state: {self.state}")

    def _leave_state(self):
        if self.state == self.next_state:
            return

        logger.debug(f"Leaving state: {self.state}")

        match self.state:
            case State.INIT:
                pass
            case State.STATE_A:
                pass
            case State.STATE_B:
                pass
            case State.ERROR:
                pass
            case State.EXIT:
                pass
            case _:
                logger.error(f"Leave State Error: Forgot a state:{self.state}")

    def transition(self):
        transition_table = self.transitions.get(self.state, {})
        if self.signal is None:
            return # No transition. Stay in the same state
            
        if self.signal in transition_table:
            self.next_state = transition_table[self.signal]
            logger.debug(f"signal: {self.signal} occured, next_state: {self.next_state}")
            if self.state == self.next_state:
                logger.warning(f"Self transition: state {self.state} to {self.next_state}. Not an error. But signaling may be unecessary")
        else:
            logger.warning(f"Unhandled signal: {self.signal} in state: {self.state}")
        
        self.signal = None

    def run(self):
        while(self.exit_condition == False):
            self._enter_state()
            self._execute_state()
            self.transition()
            self._leave_state()

if __name__ == "__main__":
    sm = StateMachine()
    sm.run()