#pragma once

namespace sakabatou_algorithm {
namespace dynamic_program {

// k个鸡蛋，n层楼，求至少扔多少次鸡蛋才能确定楼层F为临界楼层，0<=F<=n，使得<=F的楼层都不会碎，>F的都会碎
int superEggDrop(int k, int n);

} // dynamic_program
} // sakabatou_algorithm
