/*
Bria Weisblat
Section: 2
 */

#include "temperature.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

// Constructor- ensure that temperatures are valid (if not, set to default)
Temperature::Temperature (double degrees, char scale){
    Temperature::makeValid(degrees, scale);
    // Establish the default format in the constructor
    storedFormat = 'D';
}

void Temperature:: Input(){

     // Ask user to input a temperature (until their input is valid)
    do {
            std::cin >> storedDegrees >> storedScale;
             if (!(Temperature::check(storedDegrees, storedScale))){
                 std::cout << "Invalid temperature. Try again " << '\n';
             }
        }
        while (!Temperature::check(storedDegrees, storedScale));

}

void Temperature::Show() const{

    // Allow this function to accept upper and lower case scales and formats
    char tempScale = toupper(storedScale);
    // Default format: type double for degrees & first letter for scale
    if (storedFormat == 'D'){
        std::cout << storedDegrees << " " << tempScale << '\n';
    }
    // Precision-1 format: fixed with one number beyond the decimal & first letter for degrees
    else if (storedFormat == 'P'){
        // Save default precision
        int oldPrecision = std::cout.precision();
        std::ios_base::fmtflags oldflags = std::cout.flags();

        std::cout << std::fixed << std::setprecision(1) << storedDegrees << " " << tempScale << '\n';
        // Revert to default precision after the precision-1 type temperature is printed
        std::cout.precision(oldPrecision);
        std::cout.flags(oldflags);
    }
    // Long format: type double for degrees & full name of the scale
    else if (storedFormat == 'L'){
        if (tempScale == 'C'){
            std::cout << storedDegrees << " Celsius" << '\n';
        }
        else if (tempScale == 'F') {
            std::cout << storedDegrees << " Fahrenheit" << '\n';
        }
        else if (tempScale == 'K') {
            std::cout << storedDegrees << " Kelvin" << '\n';
        }

    }
    // If no format is assigned, print the temperature in the default format
    else {
        std::cout << storedDegrees << " " << storedScale << '\n';
    }
}

bool Temperature::Set(double degrees, char scale) {
    bool isSet;

    // If the temperature is valid, store it
    if (Temperature::check(degrees, scale)) {
        storedDegrees = degrees;
        // Ensure that the char scale is upper case
        storedScale = toupper(scale);
        isSet= true;
    }
    else {
        isSet = false;
    }
    return isSet;
}

double Temperature::GetDegrees() const{
    return storedDegrees;
}

char Temperature::GetScale() const{
    return storedScale;
}

bool Temperature::SetFormat(char format){
    bool isSet;
    format = toupper(format);
    // Don't set the format if the user enters an invalid char
    if ( (format != 'D') && (format != 'P') && (format != 'L') ){
        isSet = false;
    }
   // Set the format is the user enters a valid char
    else {
        isSet= true;
        storedFormat = format;
    }

    return isSet;
}

bool Temperature::Convert(char sc){
    bool isConvert;
    sc = toupper(sc);
    storedScale = toupper(storedScale);
    // If the current scale is the same as the desired scale, do not alter the degrees
    if (sc == storedScale){
        storedDegrees = storedDegrees + 0;
        storedScale = sc;
        isConvert = true;
    }
    // Celsius to Kelvin
    else if ( (storedScale == 'C') && (sc == 'K')){
        storedDegrees = storedDegrees + 273.15;
        storedScale = sc;
        isConvert = true;
    }
    // Celsius to Fahrenheit
    else if ( (storedScale == 'C') && (sc == 'F')){
        storedDegrees = (storedDegrees * (9.0/5.0)) + 32;
        storedScale = sc;
        isConvert = true;
    }
    // Fahrenheit to Celsius
    else if ( (storedScale == 'F') && (sc == 'C')){
        storedDegrees = (storedDegrees - 32) * (5.0/9.0);
        storedScale = sc;
        isConvert = true;
    }
    // Fahrenheit to Kelvin
    else if ( (storedScale == 'F') && (sc == 'K')){
        storedDegrees = ((storedDegrees - 32) * (5.0/9.0)) + 273.15;
        storedScale = sc;
        isConvert = true;
    }
    // Kelvin to Celsius
    else if ( (storedScale == 'K') && (sc == 'C')){
        storedDegrees = storedDegrees - 273.15;
        storedScale = sc;
        isConvert = true;
    }
    // Kelvin to Fahrenheit
    else if ( (storedScale == 'K') && (sc == 'F')){
        storedDegrees = ((storedDegrees - 273.15) * (9.0/5.0)) + 32;
        storedScale = sc;
        isConvert = true;
    }
    else {
        isConvert = false;
    }
    return isConvert;
}

int Temperature::Compare(const Temperature& d) const{
    int compareTemps = 10;

    double inputTempC;
    double callerTempC;

    // Compare temperatures if they are in the same scale
    if (d.GetScale() == storedScale) {
        if (d.GetDegrees() > storedDegrees){
            compareTemps = -1;
        }
        else if (d.GetDegrees() < storedDegrees){
            compareTemps = 1;
        }
        else if (d.GetDegrees() == storedDegrees){
            compareTemps = 0;
        }
    }
    else{
        // If the temperatures are in different scales, convert both to Celsius then compare
        inputTempC = Temperature::makeCelsius (d.GetDegrees(), d.GetScale());
        callerTempC = Temperature::makeCelsius (storedDegrees, storedScale);
        if (inputTempC > callerTempC){
            compareTemps = -1;
        }
        else if (inputTempC <  callerTempC){
            compareTemps = 1;
        }
        else if (inputTempC == callerTempC){
            compareTemps = 0;
        }
    }
    return compareTemps;
}

// Increment a temperature in a user-enter scale and # of degrees while remaining in the original scale
void Temperature::Increment(int degrees, char sc){
    // Save the original
    char originalScale = storedScale;
    // Convert the scale
    Temperature::Convert(sc);
    // Add the degrees
    storedDegrees = storedDegrees + degrees;
    // If decrementing results in a temperature below freezing, reverse it
    if (!Temperature::check(storedDegrees, storedScale)){
        storedDegrees = storedDegrees - degrees;
    }
    // Convert the scale back
    Temperature::Convert(originalScale);
}


// Ensure that temperatures are in a valid scale and above absolute freezing (if not, set the default)
void Temperature::makeValid(double degrees, char scale) {

    if ( ((scale == 'c') || (scale == 'C')) && degrees < -273.15 ){
        storedScale = 'C';
        storedDegrees = 0;
    }
    else if ( ((scale == 'f') || (scale == 'F')) && (degrees < -459.67) ){
        storedScale = 'C';
        storedDegrees = 0;
    }
    else if ( ((scale == 'k') || (scale == 'K')) && (degrees < 0) ) {
        storedScale = 'C';
        storedDegrees = 0;
    }
    else if ( (scale != 'c') && (scale != 'C') && (scale != 'f') && (scale != 'F') && (scale != 'k') && (scale != 'K') ){
        storedScale = 'C';
        storedDegrees = 0;
    }
    else {
        storedScale = toupper(scale);
        storedDegrees = degrees;
    }
}



// Check to see if temperatures are in a valid scale and above absolute freezing
bool Temperature::check(double degrees, char scale){
    bool isValid = true;
    if ( ((scale == 'c') || (scale == 'C')) && degrees < -273.15 ){
        isValid = false;
    }
    else if ( ((scale == 'f') || (scale == 'F')) && (degrees < -459.67) ){
        isValid = false;
    }
    else if ( ((scale == 'k') || (scale == 'K')) && (degrees < 0) ) {
        isValid = false;
    }
    else if ( (scale != 'c') && (scale != 'C') && (scale != 'f') && (scale != 'F') && (scale != 'k') && (scale != 'K') ){
        isValid = false;
    }
    return isValid;
}

// Converts a temperature to Celsius
double Temperature::makeCelsius (double degrees, char scale) const {
    if (scale == 'C'){
        return degrees;
    }
    else if (scale == 'K'){
        return degrees - 273.15;
    }
    else if (scale == 'F'){
        return (degrees - 32) * (5.0/9.0);
    }
}




