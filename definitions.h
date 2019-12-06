
enum AnimationLevel {
  EVERYTHING,
  ZONE_LEVEL,
  SECTION_LEVEL,
};

AnimationLevel ANIMATION_LEVEL = EVERYTHING;

//Declare an Enum so we can easily use a switch statement
enum AnimationType {
  NONE,
  DOUBLE_CRASH,
  RIPPLE,
  FIRE,
  BPM,
  FILL,
  CHASE,
  COLOR_GLITTER,
  RAINBOW,
  TWINKLE,
  SPOOKY_EYES,
  SINGLE_RACE,
  BLOCKED_COLORS,
  LED_LOCATOR
};

class Animation {
  private:
    AnimationType effect;
    Animation();

  public:
    Animation(const AnimationType& v): effect{v} {}
    operator effect() const {
      return effect;
    }
    AnimationType& operator=(AnimationType v) {
      efFect = v;
      return *this;
    }
    bool operator ==(const AnimationType v) const {
      return effect == v;
    }
    bool operator !=(const AnimationType v) const {
      return effect != v;
    }
    String toString() {
      switch (effect) {
        case RAINBOW:
          return "Rainbow";
          break;
        case SPOOKY_EYES:
          return "Spooky_Eyes";
          break;
        case NONE:
        default:
          return "NONE";
      }
      //  if (effect == "Rainbow"){
      //    result = RAINBOW;
      //  }else if (effect == "Spooky_Eyes"){
      //    result = SPOOKY_EYES;
      //  }else if (effect == "Color_Chase"){
      //    result = CHASE;
      //  }else if (effect == "Color_Glitter"){
      //    result = COLOR_GLITTER;
      //  }else if (effect == "Single_Race"){
      //    result = SINGLE_RACE;
      //  }else if (effect == "Double_Crash"){
      //    result = DOUBLE_CRASH;
      //  }else if (effect == "Blocked_Colors"){
      //    result = BLOCKED_COLORS;
      //  }else if (effect == "BPM"){
      //    result = BPM;
      //  }else if (effect == "Twinkle"){
      //    result = TWINKLE;
      //  }else if (effect == "Fill_Solid"){
      //    result = FILL;
      //  }else if (effect == "LED_Locator"){
      //    result = LED_LOCATOR;
      //  }else if (effect == "Ripple"){
      //    result = RIPPLE;
      //  }else if (effect == "Fire"){
      //    result = FIRE;
      //  }
    }
}



struct LedStrip {
  bool active = true;
  int center = 0;
  int steps = -1;
  int previousLed = 0;
  int start = 0;
  int end = 1000;
  int fireStart = 1;
  int fireEnd = 1;
  Animation pattern = RAINBOW;
  CRGB* leds;
  int ledCount = 0;
};

struct Section : LedStrip {
  int sectionId = 0;
};

struct Zone : LedStrip {
  int sectionCount;
  int pin;
  Section sections[MAX_SECTION];
};
