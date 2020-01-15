#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

static const char delims[] = ".!?;:";

using namespace std;

bool isDelimeter(char sym) {
  size_t i = 0;
  char delim;
  while ((delim = delims[i++])) {
    if (delim == sym) {
      return true;
    }
  }

  return false;
}

bool comparator(string &a, string &b) {
  bool result = false;

  if (a[1] == ' ' || a[1] == ',') {
    result = true;
  }

  return result;
}

int main(void) {
  cout << "== Files read/write sample. ==" << endl << endl;

  // FILE *in = fopen("data/sample", "r");
  // FILE *out = fopen("data/out", "w");

  ifstream in("data/sample");
  ofstream out("data/out");

  if (in.bad() || out.bad()) {
    exit(EXIT_FAILURE);
  }

  vector<string> sentences;

  char sym;
  bool done = false;

  do {
    string str = "";
    bool newStr = true;

    while (true) {
      in.get(sym);
      if ((done = in.eof())) {
        break;
      }

      if (newStr) {
        if (sym == ' ' || sym == '\n') {
          continue;
        }

        newStr = false;
      }
      else if (sym == '\n') {
        continue;
      }

      str += sym;

      if (isDelimeter(sym)) {
        break;
      }
    }

    sentences.push_back(str);

  } while (!done);

  sort(sentences.begin(), sentences.end(), comparator);

  for (auto str: sentences) {
    cout << str << endl << endl;
    out << str << endl << endl;
  }

  in.close();
  out.close();

  exit(EXIT_SUCCESS);
}
