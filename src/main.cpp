#include <iostream>
#include <string>

#include "core/http/http.h"
#include "core/http/httpClient/httpClient.h"
#include "core/http/parser.h"
#include "core/locationiq/locationiq.h"

static void on_received_full_message(HTTPClient *client)
{
    std::cout << client->inbuffer << "\n";
}

int main()
{
    HTTPClient client;

    HTTPClient_Initiate(&client, on_received_full_message);

    std::cout << "\n\n===============================================================\n";
    std::cout << "Hello & Welcome to Chas Malmö Utvecklingsbyrå's Weather Client!\n";
    std::cout << "===============================================================\n";

    while (true)
    {
        std::cout << "\nPlease select one of the following two options:\n\nPress 1: to write the name of a location.\nPress 2: to input the latitude and longitude of the location.\nHowever, if you would like to exit the program just enter 'e' or 'q'\n";
        std::cout << "\rPlease make your choice: \n";
        
        std::string input_buffer;

        std::cin >> input_buffer;

        if ((input_buffer.compare("exit") == 0) || (input_buffer.compare("quit") == 0) || (input_buffer.compare("e") == 0) || (input_buffer.compare("q") == 0))
            break;
        
        int selected_menu_choice = stoi(input_buffer);

        if (selected_menu_choice == 1)
            std::cout << "1 selected\n";

        float latitude = 0.0f;
        float longitude = 0.0f;

        switch (selected_menu_choice)
        {
            case 1:
            {
                std::string input;
                Coordinates coords;
                
                std::cout << "Please enter city name: \n";
                std::cin >> input;

                if (input.compare("0") == 0)
                    break;

                if (input.length() == 0)
                {
                    std::cout << "City name cannot be empty. Try again.\n";
                    continue;
                }

                const char* city_name = input.c_str();
                LOCATIONIQ_RESULT result = (LOCATIONIQ_RESULT)locationiq_get_coordinates(&coords, city_name);

                if (result == LOCATIONIQ_RESULT_USER_ABORTED)
                    continue;

                if (result != LOCATIONIQ_RESULT_OK)
                {
                    std::cout << "No matching cities found.\n";
                    continue;
                }

                latitude = coords.lat;
                longitude = coords.lon;

                std::cout << "Found city: " << coords.location << "\n";
                std::cout << "lat=" << latitude << "\nlon=" << longitude << "\n";

                break;
            }
   
            case 2:
            {
                while (true)
                {
                    float lat, lon;

                    std::cout << "Please enter latitude (-90 to 90):\n";
                    std::cin >> lat;
                    std::cout << "Please enter longitude (-180 to 180):\n";
                    std::cin >> lon;

                    if (lat < -90 || lat > 90)
                    {
                        std::cout << "Invalid latitude value. Try again.\n";
                        continue;
                    }
                    if (lon < -180 || lon > 180)
                    {
                        std::cout << "Invalid longitdue value. Try again.\n";
                        continue;
                    }

                    break;
                }

                break;
            }

            default:
            {
                std::cout << "Invalid choice.\n";
                continue;
            }

        }
    }

    return 0;
}












/* #include "CurlHelper/CurlHelper.hpp"

int main()
{
    CurlHelper curl;

    std::cout << "In main\r\n";
    curl.httpGet("http://kontoret.onvo.se:10280/weather?latitude=55.60587&longitude=13.00073");

    curl.print_string();

    return 0;
} */