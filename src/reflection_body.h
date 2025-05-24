/* REFLECTION BODY CODE */
/**
 * This file contains the common code required by all self-reflected classes/structs.
 * To use it, ensure that you have defined a macro called FIELDS, with each field listed
 * as a typed expression wrapped in a REFLECT macro. Below is an example:
 * 
 * #define FIELDS \
 * REFLECT((int) x) \
 * REFLECT((char) y)
 * 
 * Then include this file inside of the class you wish to reflect.
**/

friend struct reflector;

#define REFLECT(field) DECL(field);
FIELDS
#undef REFLECT

public:
#define REFLECT(field) {STRINGIZE(NAMEOF(field)), STRINGIZE(TYPEOF(field))},
static inline const unordered_map<string, string> field_data = { FIELDS };
#undef REFLECT