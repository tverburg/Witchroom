// ---------------------------------------------------------
// Reset include
//
// Used for resetting components
// -------------------------------------------------------

void resetComponents() {
  #if hasPuzzles
    resetPuzzles();
  #endif
  #if hasEvents
    resetEvents();
  #endif
  #if hasLocks
    resetLocks();
  #endif
  #if hasEffects
    resetEffects();
  #endif
  #if hasTimer
    resetTimer();
  #endif
  #if hasHints
    resetHints();
  #endif
}