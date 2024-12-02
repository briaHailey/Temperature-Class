#include "temperature.h"
#include <iostream>

int main() {
    // Test the default constructor (should set to 0 C)
    Temperature t1;
    std::cout << "Test the default \n";
    t1.Show();

    // Test the constructor with inputs
    Temperature t2(100, 'F');
    std::cout << "Test the constructor with inputs \n";
    t2.Show();

    // Test the constructor with incorrect inputs
    Temperature t3(1, 'K');
    std::cout << "Test the constructor with incorrect inputs \n";
    t3.Show();

    // Test the constructor with lowercase inputs
    Temperature t4(-203, 'C');
    std::cout << "Test the constructor with lowercase inputs \n";
    t4.Show();

    // Test input function
    std:: cout << "Test the input function. Input a temperature: \n";
    t1.Input();
    std:: cout << "Show the input temperature \n";
    t1.Show();


    // Try different formats
    std:: cout << "Precise format (one number after the decimal) \n";
    t1.SetFormat('P');
    t1.Show();
    std:: cout << "Long format (full name of the scale) \n";
    t1.SetFormat('L');
    t1.Show();
    std:: cout << "Default format (classic double) \n";
    t1.SetFormat('D');
    t1.Show();

    // Try an incorrect format
    std:: cout << "Try an incorrect format (sets to default)  \n";
    t1.SetFormat('F');
    t1.Show();

    //Test set function
    std:: cout << "Test the set function (-300 F)  \n";
    t3.Set(-300, 'F');
    t3.Show();

    // Test conversion function
   std::cout << "Before conversion: ";
   t1.Show();
   std::cout << "After conversion: ";
   t1.Convert('K');
   t1.Show();

    // Test accessors
    std::cout << "Test the accessors ";
    std::cout << "\nt1's degrees is: " << t1.GetDegrees() << "\nt1's scale is: " << t1.GetScale() << '\n';

    // Test comparison function
    std::cout << "Test comparison function ";
    std::cout << "t1 compared to t2 returns: " << t1.Compare(t2) << '\n';

    // Test increment function
    std::cout << "Test the increment function ";
    t1.Set(0, 'K');
    t1.Increment(-5, 'F');
    t1.Show();

    return 0;
}





