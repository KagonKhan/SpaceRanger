#pragma once



#pragma warning(push, 0)



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>


#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
#include <queue>
#include <deque>

#include <functional>
#include <utility>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <optional>
#include <iomanip>
#include <random>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "boost/log/trivial.hpp"


#pragma warning(pop)



#include "Button.h"
#include "ArrowSwitchTextButton.h"
#include "CheckboxButton.h"
#include "SpriteButton.h"
#include "TextButton.h"

#include "Layout.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "TableLayout.h"
#include "UnorderedLayout.h"

#include "Configuration.h"
#include "Helpers.h"


constexpr long double M_PIl = 3.141592653589793238462643383279502884L; /* pi */
