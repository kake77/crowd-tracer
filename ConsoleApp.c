#include <stdio.h>
#include <stdlib.h>
//通路の構造体
struct edge;
//分岐点または終点（教室の構造体）
struct node {
	struct edge* connected[3];//つながっている通路
	int floor;//何階にあるか
	int type;//0 room,1 branch
	int id;//教室id
};
struct edge {
	struct node* connected[2];//つながっている教室または分岐点
	int floor;//何階にあるか　階をまたぐ場合はconnected[0]の階
	int time;//渡るのに必要な時間
	int maxNPeople;//その区間に入れる最大人数
	int isEsca;//0 no, 1 up, 2 down
	int nPeople;//その区間にいる人数
};

typedef struct node Node;
typedef struct edge Edge;

#define NN (25)
#define NE (26)
//Edgeのポインタからidを計算する関数
int edgeId(Edge* e0, Edge* e) {
	return ((int)e - (int)e0) / sizeof(Edge);
}

int main() {
	//教室または分岐点を表すノードを配列として定義
	Node Nodes[NN];
	for (int i = 0; i < NN; i++) {
		Nodes[i].id = i;
		for (int j = 0; j < 3; j++) {
			Nodes[i].connected[j] = NULL;
		}
	}
	//通路を定義
	//ここで何処と何処が繋がっているか、その通路の距離なども宣言する
	Edge Edges[26] = {
		{{&Nodes[0],&Nodes[1]},1,10,20,0,0},
		{{&Nodes[1],&Nodes[2]},1,10,20,0,0},
		{{&Nodes[2],&Nodes[3]},1,10,20,0,0},
		{{&Nodes[2],&Nodes[4]},1,10,20,0,0},
		{{&Nodes[4],&Nodes[5]},1,10,20,0,0},
		{{&Nodes[4],&Nodes[6]},1,10,20,0,0},
		{{&Nodes[0],&Nodes[11]},1,10,20,1,0},
		{{&Nodes[7],&Nodes[8]},2,10,20,0,0},
		{{&Nodes[8],&Nodes[9]},2,10,20,0,0},
		{{&Nodes[8],&Nodes[10]},2,10,20,0,0},
		{{&Nodes[10],&Nodes[11]},2,10,20,0,0},
		{{&Nodes[10],&Nodes[12]},2,10,20,0,0},
		{{&Nodes[12],&Nodes[13]},2,10,20,0,0},
		{{&Nodes[12],&Nodes[14]},2,10,20,0,0},
		{{&Nodes[14],&Nodes[15]},2,10,20,0,0},
		{{&Nodes[14],&Nodes[16]},2,10,20,0,0},
		{{&Nodes[7],&Nodes[1]},2,10,20,2,0},
		{{&Nodes[11],&Nodes[17]},2,10,20,1,0},
		{{&Nodes[17],&Nodes[18]},3,10,20,0,0},
		{{&Nodes[17],&Nodes[19]},3,10,20,0,0},
		{{&Nodes[19],&Nodes[7]},3,10,20,2,0},
		{{&Nodes[19],&Nodes[20]},3,10,20,0,0},
		{{&Nodes[20],&Nodes[21]},3,10,20,0,0},
		{{&Nodes[20],&Nodes[22]},3,10,20,0,0},
		{{&Nodes[22],&Nodes[23]},3,10,20,0,0},
		{{&Nodes[22],&Nodes[24]},3,10,20,0,0},
	};
	//エッジで定義したものをノードにも情報を伝える
	for (int i = 0; i < NE; i++) {
		Edge* e = &Edges[i];
		for (int j = 0; j < 2; j++) {
			Node* n = e->connected[j];
			for (int k = 0;k<3; k++) {
				if (n->connected[k] == NULL) {
					n->connected[k] = e;
					break;
				}
			}
			if (j == 1 && e->isEsca == 1) {
				n->floor = e->floor+1;
				continue;
			}
			if (j == 1 && e->isEsca == 2) {
				n->floor = e->floor-1;
				continue;
			}
			n->floor = e->floor;
		}
	}
	for (int i = 0; i < NN; i++) {
		int count = 0;
		for (int j = 0; j < 3; j++) {
			if (Nodes[i].connected[j] != NULL)count++;
		}
		if (count > 1) {
			Nodes[i].type = 1;
		}
		else {
			Nodes[i].type = 0;
		}
	}
  //テスト用出力
	for (int i = 0; i < NN; i++) {
		if (Nodes[i].type == 0) {
			printf("%d,%d,部屋,%d\n", Nodes[i].id, Nodes[i].floor, edgeId(Edges, Nodes[i].connected[0]));
		}
		else {
			printf("%d,%d,分岐,%d,%d,%d\n", Nodes[i].id, Nodes[i].floor, edgeId(Edges, Nodes[i].connected[0]), edgeId(Edges, Nodes[i].connected[1]), edgeId(Edges, Nodes[i].connected[2]));
		}
	}
	
}
