#ifndef _MPISLAVE_H_
#define _MPISLAVE_H_

class GPConfig;
void mpislave(int myMPIid, int numberOfNodes, int popSize, GPConfig *conf);

#endif
