class DuplicateTradeException
    : public std::runtime_error
{
public:
    explicit DuplicateTradeException(
        std::uint64_t tradeId)
        :
        std::runtime_error(std::format(
                "Trade {} already exists",
                tradeId))
    {
    }
};