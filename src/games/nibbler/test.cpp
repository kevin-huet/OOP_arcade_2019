#include <chrono>
#include <thread>
#include <iostream>
 
int main()
{
    std::chrono::seconds interval( 2 ) ; // 10 seconds
    //for( int i = 0 ; i < 10 ; ++i )
    //{
       std::cout << "tick!\n" << std::flush ;
       std::this_thread::sleep_for( interval ) ;
    //}
}