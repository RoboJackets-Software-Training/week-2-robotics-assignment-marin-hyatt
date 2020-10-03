#include <iostream>  // Gives us access to std::cin and std::cout
#include <string>  // Gives us access to std::string and std::getline()

struct LightOutputs {
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs {
  bool car_sensor_n;
  bool car_sensor_s;
};

// TODO Define your light controller state machine class here
class LightController {
public:
  LightOutputs update(LightInputs input) {
    //take in input
    switch (current_state) {
      case (RR) :
        if (input.car_sensor_s == 1 || input.car_sensor_n == 1) {
          current_state = RG;
          time_since_light_change += 1;
        } else {
          current_state = GR;
          time_since_light_change += 1;
        }
        break;
      case (GR) :
        if (lightChange()) {
          //change to yellow
          current_state = YR;
          time_since_light_change = 1;
        } else {
          time_since_light_change += 1;
        }
        break;
      case (RG) :
        if (lightChange()) {
          //change to yellow
          current_state = RY;
          time_since_light_change = 1;
        } else {
          time_since_light_change = 1;
        }
        break;
      case (YR) :
        if (lightChange()) {
          //change to red
          current_state = RR;
          time_since_light_change = 1;
        } else {
          time_since_light_change += 1;
        }
        break;
      case (RY) :
        if (lightChange()) {
          current_state = RR;
          time_since_light_change = 1;
        } else {
          time_since_light_change += 1;
        }
        break;
    }
    
    return getLights();
  }

private:
  int time_since_light_change = 1;

  //declare states;
  enum State {
    RR,
    GR,
    RG,
    RY,
    YR
  };

  State current_state = RR;

  //check if light can be changed
  bool lightChange() {
    if (current_state == GR || current_state == RG) {
      return (time_since_light_change >= 5);
    } else {
      //at least one light is yellow
      return (time_since_light_change >= 2);
    }
  }

  //method to return LightOutputs from state
  LightOutputs getLights() {
    //checks all states (only 1 should be true)
    switch(current_state) {
      case (RR):
        return {true, false, false, true, false, false};
        break;
      case (GR):
        return {true, false, false, false, false, true};
        break;
      case (RG):
        return {false, false, true, true, false, false};
        break;
      case (YR):
        return {true, false, false, false, true, false};
        break;
      case (RY) :
        return {false, true, false, true, false, false};
        break;
    }
  }
};

int main()
{
    // TODO Initialize your state machine class here
    LightController controller;

    while(true)
    {
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;

        // TODO Parse the input digits
        LightInputs inputs = {
          input[0] == 1,
          input[1] == 1
        };

        // TODO Update your state machine based on input
        LightOutputs output = controller.update(inputs);

        // TODO Output your state machine's light controls to std::cout
        std::cout << output.red_ns << output.yellow_ns << output.green_ns
                  << output.red_ew << output.yellow_ew << output.green_ew << "\n";
    }
    return 0;
}
