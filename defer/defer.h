#ifndef CUTILS_DEFER
#define CUTILS_DEFER

#define dreturn goto DEFER_BODY;

#define BODY(content) \
FUNC_BODY: \
{content} \
goto DEFER_BODY;


#define DEFER(deferblock) \
goto AFTER_DEFER; \
DEFER_BODY: \
{deferblock} \
AFTER_DEFER: \

#define DEFERABLE(deferdef) deferdef; goto FUNC_BODY;

#endif // CUTILS_DEFER