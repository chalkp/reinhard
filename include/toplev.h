#pragma once

class toplev {
public:
  toplev();
  ~toplev();

  int main(int argc, char **argv);
  void finalize();

private:
  void run_self_test();
};
