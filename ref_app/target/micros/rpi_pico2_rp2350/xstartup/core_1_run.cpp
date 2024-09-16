
namespace local
{
  auto core_1_run_flag() -> bool&;

  auto core_1_run_flag() -> bool&
  {
    static bool run_flag { false };

    return run_flag;
  }
}

extern "C"
{
  auto core_1_run_flag_set(bool setting) -> void;
  auto core_1_run_flag_get(void) -> bool;

  auto core_1_run_flag_set(bool setting) -> void
  {
    local::core_1_run_flag() = setting;
  }

  auto core_1_run_flag_get(void) -> bool
  {
    const bool result { local::core_1_run_flag() };

    return result;
  }
}
