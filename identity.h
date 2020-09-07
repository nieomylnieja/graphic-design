/* Used to help with generic methods
 * which require type itself as a parameter */

template<typename T>
struct identity {
    typedef T type;
};
