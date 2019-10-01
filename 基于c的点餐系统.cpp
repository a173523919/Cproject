#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
//定义：菜品
struct   dish {
	int price;
	char name[30];

};

//定义：订单
struct order{
	int tablenumber;
	int state;
	int dishamount;
	struct dish dishes[100];
};

int main()
{
	int flag = 0;
	int loop = 1;
	int i = 0;
	int j = 0;
	int maxtable = 10;

	struct dish menu[100];
	for (i = 0; i < 100; i++) {
		menu[i].price = 0;
	}
	char dishname[100];

	struct order orders[100];
	for (i = 0; i < 100; i++) {
		orders[i].dishamount = 0;
		orders[i].state = 0;
	}
	i = 0;

	int table[10];
	for (i = 0; i < 10; i++) {
		table[i] = 0;
	}
	i = 0;
	int dishamount = 0;
	int orderamount = 0;
	int tnum = 0;
	int income = 0;
	char orderstate[20];

	printf("------------------");
	printf("\n欢迎使用点餐系统\n");
	printf("------------------");

	while (loop) {
		printf("\n请输入操作码\n");
		printf("1.查看菜单\n");
		printf("2.添加菜品\n");
		printf("3.删除菜品\n");
		printf("4.选桌点餐\n");
		printf("5.结账\n");
		printf("6.导出今日账单\n");
		printf("0.退出系统\n");

		scanf("%d", &flag);
		
		//查看菜单
		if (flag == 1) {
			if (dishamount==0) {
				printf("当前没有菜品可提供\n");
			}
			for (i = 0; i < dishamount; i++) {
				printf("菜品%d：%s\n",i+1,menu[i].name);
				printf("菜品价格：%d\n", menu[i].price);
			}
			i = 0;
		}

		//添加菜品
		if (flag == 2) {
			printf("\n请输入菜品名称\n");
			scanf("%s",&dishname);
			strcpy(menu[dishamount].name,dishname);
			printf("请输入菜品价格\n");
			scanf("%d", &menu[dishamount].price);
			dishamount++;
			printf("确定吗?1确定0取消");
			scanf("%d", &i);
			if (i == 0) {
				dishamount--;
				menu[dishamount].price = 0;
				strcpy(menu[dishamount].name, "");
				printf("操作已经撤销！\n");
			}
			else
			{
				for (i = 0; i < dishamount-1; i++) {
					if ((strcmp(dishname, menu[i].name) == 0)) {
						j = -1;
						printf("\n该餐品已经添加过了！！\n");
					}
				}
				i = 0;
				if (j<0) {
					dishamount--;
					menu[dishamount].price = 0;
					strcpy(menu[dishamount].name, "");
					printf("操作已经撤销！\n");
				}
				else {
					printf("菜品添加成功！");
				}
				
			}
			i = 0;
			j = 0;
			
		}
		//删除菜品
		if (flag == 3) {
			printf("\n请输入要删除的菜品名称\n");
			scanf("%s", &dishname);
			for (i = 0; i < dishamount; i++) {
				if ((strcmp(menu[i].name, dishname)== 0)) {
					j = 1;
					break;
				}
			}
			if (j == 0) {
				printf("要删除的菜品不存在，请核对！\n");
			}
			else {
				j = i;
				//前顶删除
				for (i=j; i<dishamount-1; i++) {
					strcpy(menu[i].name, menu[i + 1].name);
					menu[i].price = menu[i + 1].price;
				}
				//前顶删除后把最后一个无用的变量kill掉
				menu[dishamount].price = 0;
				strcpy(menu[dishamount].name, "");
				dishamount--;
				printf("删除成功！\n");
			}
			i = 0;
			j = 0;
		}

		//选坐点餐
		if (flag == 4) {
			tnum = 0;
			//查询空桌子
			for (i = 1; i < maxtable; i++) {
				if (table[i] == 0) {
					printf("第%d号桌是空的\n",i);
					tnum++;
				}
			}
			i = 0;
			printf("查询到%d个空桌\n", tnum);
			
			printf("请输入桌号\n");
			scanf("%d", &tnum);
			//验证输入的餐桌是否可用
			if ((table[tnum] == 1)||(tnum>maxtable-1)||(tnum<1)) {
				printf("桌号错误，请重新选择！\n");
			}
			else {
				//桌号可用，占桌，生成没有支付的原始订单
				table[tnum] = 1;
				orders[orderamount].tablenumber = tnum;
				orders[orderamount].state = 0;
				i = 1;
				//循环执行点餐
				while (i) {
				printf("\n------当前桌号%d-------\n", tnum);
				printf("\n------请点餐-------\n");
				
				if (dishamount == 0) {
					printf("当前没有菜品可提供\n");
				}
				for (i = 0; i < dishamount; i++) {
					printf("菜品%d：%s\n", i+1, menu[i].name);
					printf("菜品价格：%d\n", menu[i].price);
				}
				i = 0;
				printf("\n------请点餐-------\n");
				printf("请输入菜品名称\n");
				//将菜品名称写入order结构体的dish数组变量中
				scanf("%s", &orders[orderamount].dishes[j].name);
				printf("确定吗?1确定0取消");
				scanf("%d", &i);
				//如果取消，将菜品名称删除
				if (i == 0) {
					strcpy(orders[orderamount].dishes[j].name, "");
				}
				else {
				//验证在菜单中是否可以找到这个菜品，如果可以找到，将菜品价格写入结构体中dish数组变量
				orders[orderamount].dishes[j].price = -1;
				for (i = 0; i < dishamount; i++) {
					if ((strcmp(orders[orderamount].dishes[j].name,menu[i].name)==0)) {
						orders[orderamount].dishes[j].price = menu[i].price;
						
					}
				}
				i = 0;
				//如果菜单中找不到这个菜品，删除之前写好的菜品名称信息
				if (orders[orderamount].dishes[j].price < 0) {
					printf("\n您输入的菜品信息错误，请核对！！！\n");
					strcpy(orders[orderamount].dishes[j].name, "");
				}
				//如果菜单中找得到这个菜品，完成点单，结构体中记录菜品数量的dishamount+1
				else {
				printf("点单成功！");
				orders[orderamount].dishamount++;
				j++;
				}
				}
				printf("继续点单吗1继续0取消");
				scanf("%d", &i);
				if (i == 0) {
					orderamount++;
					j = 0;
				}
				}
			}

		}
		if (flag == 5) {
			printf("需要结账的餐桌有：");
			//查询不可用的桌号即可查出哪个餐桌没有结账
			for (i = 1; i < maxtable; i++) {
				if (table[i] == 1) {
					printf(" %d号 ",i);
				}
			}
			printf("\n");

			printf("\n请输入要结账的桌号\n");
			scanf("%d",&tnum);
			for (i = 0; i < orderamount; i++) {
				//验证输入的桌号是否正确
				if ((orders[i].tablenumber == tnum)&&(orders[i].state==0)) {
				printf("\n请核对账单\n");
				printf("订单%d，桌号%d\n", i + 1, orders[i].tablenumber);
				for (j = 0; j < orders[i].dishamount; j++) {
					printf("点餐%d，菜品名%s，价格%d\n", j+1, orders[i].dishes[j].name, orders[i].dishes[j].price);
				}
				}
			}
			printf("确定结账吗1继续0取消");
			scanf("%d", &j);
			if (j == 1) {
				printf("%d号结账成功\n", orders[i-1].tablenumber);
				orders[i-1].state = 1;
				table[tnum] = 0;
			}
			i = 0;
			j = 0;
			tnum = 0;
		}
		//结账
		if (flag == 6) {
			if (orderamount == 0) {
				printf("当前没有收入\n");
			}
			//设置订单状态，使得最终输出并不是整数0和1
			for (i = 0; i < orderamount; i++) {
				if (orders[i].state == 0) {
					strcpy(orderstate, "未完成");
				}
				else {
					strcpy(orderstate, "已完成");
				}
			//逐条输出订单：单号，桌号，状态
				printf("订单%d，桌号%d，状态:%s\n", i+1,orders[i].tablenumber,orderstate);
			//输出每条订单所包含的菜品
				for (j = 0; j < orders[i].dishamount; j++) {
					printf("点餐%d，菜品名%s，价格%d\n", j+1, orders[i].dishes[j].name,orders[i].dishes[j].price);
				}
			}
			i = 0;
		}
		//退出系统，结束循环
		if (flag == 0) {
			loop = 0;
		}
	}
}
