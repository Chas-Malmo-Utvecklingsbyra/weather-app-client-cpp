#include <iostream>
#include <string>
#include <iomanip>

extern "C"{
    #include "core/http/http.h"
    #include "core/http/httpClient/httpClient.h"
    #include "core/http/parser.h"
    #include "core/locationiq/locationiq.h"
}

#define SERVER_ADDR "malmo.onvo.se"
#define TEST_PORT 10280

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
                    std::cout << "Please enter latitude (-90 to 90):\n";
                    std::cin >> latitude;
                    std::cout << "Please enter longitude (-180 to 180):\n";
                    std::cin >> longitude;

                    if (latitude < -90 || latitude > 90)
                    {
                        std::cout << "Invalid latitude value. Try again.\n";
                        continue;
                    }
                    if (longitude < -180 || longitude > 180)
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

        std::cout << "Getting weather for latitude: " << latitude << " longitude: " << longitude << "\n";

        std::string route = "/v1/weather?latitude=" + std::to_string(latitude) + "&longitude=" + std::to_string(longitude);
        
        HTTPClient_Reset(&client);

        HTTPClient_GET(&client, "155.4.19.176", route.c_str());

        while (HTTPClient_Work(&client) == false)
        {

        }
    }

    HTTPClient_Dispose(&client);
    std::cout << "Goodbye and thank you for using our Weather Client!\n";

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