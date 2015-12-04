////
//// Created by Evan King on 11/10/15.
////
//
//#include <assert.h>
//#include <stdlib.h>
//#include "Hashtable.h"
//
//int main() {
//    struct hashtable a;
//    hashtable_create(&a);
//    hashtable_put(&a,0,99);
//    hashtable_stats(&a); /* prints: "length = 1, N = 2, puts = 1\n" */
//    hashtable_put(&a, 1, 42);
//    hashtable_stats(&a);
//    assert(hashtable_get(&a, 0) == 99);
//    hashtable_remove(&a, 0);
//    hashtable_get(&a, 0); /* causes program to exit with exit code 1 */
//    hashtable_remove(&a, 0); /* would also cause program to exit with exit code 1 */
//    free(&a);
//    return 0;
//
//}