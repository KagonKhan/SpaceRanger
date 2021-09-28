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


#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"



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


typedef std::optional<std::reference_wrapper<Widget>> opt_ref;




typedef std::unique_ptr<HorizontalLayout>	HorLayPtr;
typedef std::unique_ptr<TableLayout>		TabLayPtr;
typedef std::unique_ptr<UnorderedLayout>	UnoLayPtr;
typedef std::unique_ptr<VerticalLayout>		VerLayPtr;

typedef std::unique_ptr<ArrowSwitchTextButton>	ArrButPtr;
typedef std::unique_ptr<CheckboxButton>			CheLayPtr;
typedef std::unique_ptr<SpriteButton>			SprLayPtr;
typedef std::unique_ptr<TextButton>				TexLayPtr;



# define M_PIl          3.141592653589793238462643383279502884L /* pi */
