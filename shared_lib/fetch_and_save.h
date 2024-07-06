#ifndef FETCH_AND_SAVE_H
#define FETCH_AND_SAVE_H

#include <string>
#include <vector>

void fetchAndSave(const std::string& branch);
void fetchAndSaveMultiple(const std::vector<std::string>& branches);

#endif // FETCH_AND_SAVE_H
