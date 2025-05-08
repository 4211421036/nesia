#ifndef ERROR_H
#define ERROR_H

// Laporan error leksikal, sintaks, dan runtime
void errorLexer(int line, const char *msg);
void errorParser(int line, const char *msg);
void errorRuntime(int line, const char *msg);

#endif // ERROR_H
