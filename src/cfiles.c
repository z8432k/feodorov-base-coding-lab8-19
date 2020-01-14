#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <glib.h>

static const char delims[] = { '.', '!', '?', ';', ':', '\0' };

gboolean isDelimeter(char sym) {
  size_t i = 0;
  char delim;
  while ((delim = delims[i++])) {
    if (delim == sym) {
      return TRUE;
    }
  }

  return FALSE;
}

void freeSentence(gpointer data) {
  g_string_free((GString *) data, TRUE);
}

void eachSentence(gpointer strPtr, gpointer dataPtr) {
  GString *str = (GString *) strPtr;
  FILE *out = (FILE *) dataPtr;

  printf("%s\n\n", str->str);
  fprintf(out, "%s\n\n", str->str);
}

gint comparator(gconstpointer a, gconstpointer b) {
  GString *strA = *(GString **) a;
  GString *strB = *(GString **) b;

  gint result = 0;

  if (strA->str[1] == ' ' || strA->str[1] == ',') {
    result--;
  }

  if (strB->str[1] == ' ' || strB->str[1] == ',') {
    result++;
  }

  return result;
}

int main(void) {
  printf("== Files read/write sample. ==\n\n\n");

  FILE *in = fopen("data/sample", "r");
  FILE *out = fopen("data/out", "w");

  if (in == NULL || out == NULL) {
    exit(EXIT_FAILURE);
  }

  // Sentences
  GPtrArray *sentences = g_ptr_array_new_with_free_func(freeSentence);

  char sym;
  gboolean done = FALSE;
  do {
    GString *str = g_string_new('\0');

    gboolean newStr = TRUE;
    while ((sym = getc(in))) {
      if ((done = (sym == EOF))) {
        break;
      }

      if (newStr) {
        if (sym == ' ') {
          continue;
        }

        newStr = FALSE;
      }
      else if (sym == '\n') {
        continue;
      }

      g_string_append_c(str, sym);

      if (isDelimeter(sym)) {
        break;
      }
    }

    g_ptr_array_add(sentences, str);

  } while(!done);

  g_ptr_array_sort(sentences, comparator);
  g_ptr_array_foreach(sentences, eachSentence, (gpointer) out);

  g_ptr_array_free(sentences, TRUE);
  fclose(in);
  fclose(out);

  exit(EXIT_SUCCESS);
}
