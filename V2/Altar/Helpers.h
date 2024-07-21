// ---------------------------------------------------------
// Helpers include
//
// Used for help functions that can be used thruout entire controller
//
// Predefined functions below remove if not needed
//
// Add functions below
// -------------------------------------------------------

//can be used to convert int array to string. Only useble with fixed data size. example: [5,2,6,6,2,3] --> "526623"
String convertIntArrayToString(int ints[], int size) {
  //handle resetting effects
  String string = "";

  for (int i=0; i<size; i++)
  {
    string += String(ints[i]);
  } 

  return string;
}
