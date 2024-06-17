#include "Operator.hpp"

bool operator==(const Couleur &couleur1, const Couleur &couleur2)
{
    if (couleur1.R == couleur2.R && couleur1.G == couleur2.G && couleur1.B == couleur2.B)
        return true;
    return false;
}