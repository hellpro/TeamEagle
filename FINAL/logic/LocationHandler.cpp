#include "LocationHandler.h"
#include <iostream>
LocationHandler::LocationHandler()
{
    has_list = false;
}


void LocationHandler::add_location(Location location) {
    if(!validate_location_name(location.get_name())) {
        throw InvalidAlphaNumException();
    }

    if(!validate_duplicate(location.get_name())) {
        throw InvalidName();
    }

    loc_repo.write(location);
    locations.push_back(location);
}

vector<Location> LocationHandler::get_locations() {
    got_list();
    return locations;
}

bool LocationHandler::validate_location_name(string location) {
    for(unsigned int i = 0; i < location.size(); i++) {
        if(!isalnum(location[i]) && !isspace(location[0])) {
            return false;

        }
    }
    return true;
}

bool LocationHandler::validate_duplicate(string location) {
    got_list();
    for(unsigned int i = 0; i < locations.size(); i++) {
        if(locations.at(i).get_name() == location) {
            return false;
        }
    }
    return true;
}

void LocationHandler::got_list() {
    if(!has_list) {
        locations = loc_repo.read();
        has_list = true;
    }
}

void LocationHandler::remove_location(int index) {
    if(index < 0 || (unsigned)index >= locations.size()) {
        throw InvalidSize();
    }

    locations.erase(locations.begin() + index);
    loc_repo.overwrite(locations);
}

