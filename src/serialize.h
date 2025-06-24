// MAKE THIS INTO A SEPERATE HEADER
enum GQ_RETURN_CODE
{
    GQ_ERR,
};

// Aha
class Serialize
{
    virtual ~Serialize() = default;
    virtual GQ_RETURN_CODE Load() = 0;
    virtual GQ_RETURN_CODE Store() = 0;
};