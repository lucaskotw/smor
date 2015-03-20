/**
 * Return the index of maximum in the given vector
 */


int ArgMax(VectorXd vec) {
    int idx = -1; // initialize selected idx
    int curr_max = -1;
    for (int i=0; i<vec.size(); ++i) {
        if (vec.at(i) > curr_max) {
            idx = i;
            curr_max = vec.at(i);
        }
    }

    return idx;
}