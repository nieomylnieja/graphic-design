#ifndef GRAPHIC_DESIGN_IDENTITY_H
#define GRAPHIC_DESIGN_IDENTITY_H

/* Used to help with generic methods
 * which require type itself as a parameter */

template<typename T>
struct identity {
    typedef T type;
};

#endif