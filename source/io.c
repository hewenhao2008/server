/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 网络IO同本地IO的实现。
*/

/* 读socket@一直读直至内核缓冲区没数据为止 */
int rdsock(int sock, char *buffer)
{
    return 0;
}

/* 写socket@一直写直至无数据 */
int wrsock(int sock, char *buffer, int bytes)
{
    return 0;
}
