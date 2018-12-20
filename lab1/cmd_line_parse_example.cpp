#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;

void on_p2(int p2)
{
  std::cout << "on_p2 notifier: " << p2 << '\n';
}

int main(int argc, const char *argv[])
{
  try
  {
    options_description desc{"Options"};
    desc.add_options()
      ("-help,h", "Usage: p1 - param1, p2 - param2")
      ("p1", value<float>()->default_value(3.14f), "Param1")
      ("p2", value<int>()->notifier(on_p2), "Param2");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
      std::cout << desc << '\n';
    else if (vm.count("p1"))
      std::cout << "Param1: " << vm["p1"].as<float>() << '\n';
    else if (vm.count("p2"))
      std::cout << "Param2: " << vm["p2"].as<int>() << '\n';
  }
  catch (const error &ex)
  {
    std::cerr << ex.what() << '\n';
  }
}
