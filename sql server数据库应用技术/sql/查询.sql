--T-SQL查询(1)使用WITH公用表表达式查看客户名称为’大连航运公司’在北京市的所有上级主管单位代码和单位名称
GO
WITH CTE_CLIENT (SNO) AS (
  SELECT SNO 
  FROM Customer 
  WHERE CNAME = '大连航运公司'
  UNION ALL   --递归CTE
  SELECT Customer.SNO 
  FROM CTE_CLIENT, Customer 
  WHERE Customer.CNO = CTE_CLIENT.SNO
)
SELECT C.CNO, CNAME 
FROM Customer C, CTE_CLIENT CTE
WHERE C.CCITY = '北京' AND C.CNO = CTE.SNO
ORDER BY C.CNO;

--T-SQL查询(2)查询客户名称为’教育部’在2023年所订购的大于其最小订购数量的2倍的杂志代码、杂志名称及订购数量
GO
WITH 
Orders AS (
SELECT OL.Mno AS Mno,SUM(OL.Onum) AS sumnum
    FROM OrderList OL
    JOIN OrderH OH ON OL.Ono = OH.Ono
    JOIN Customer  ON Customer.Cno = OH.Cno
    WHERE Customer.Cname = '教育部'
    AND YEAR(OH.Odate) = 2023 
	GROUP BY OL.Mno),--同一客户可能存在不同订单,不同订单可能存在相同杂志与SUM(OrderList.Onum)联合使用求出相同杂志的总订购数
Minorders AS (
	SELECT MIN(Orders.sumnum)*2 AS minnum
	FROM Orders)
SELECT O.Mno,M.Mname,O.sumnum
FROM  Orders O,Minorders,Magazine M
WHERE M.Mno=O.Mno and O.sumnum > Minorders.minnum;

--T-SQL查询(3)使用TOP和查询结果集别名表达式，查询杂志名称为’散文随笔’、2023年订购数量为第2-5名的客户代码、客户名称和订购数量（设’读者’的订购客户数>=5）
GO
WITH Result AS (
SELECT TOP 4 desctop5.Cno,sum(desctop5.Onum) AS sumnum FROM
( SELECT TOP 5 C.Cno, SUM(OL.Onum)
					FROM Magazine M
					LEFT JOIN OrderList OL ON M.Mno = OL.Mno 
					LEFT JOIN OrderH OH ON OL.Ono = OH.Ono 
					LEFT JOIN Customer C ON OH.Cno = C.Cno 
					WHERE M.Mname = '散文随笔'AND YEAR(OH.Odate)=2023
					GROUP BY C.Cno  --一名客户可以在不同订单订购同一本书,需要按照客户代码进行分组
					ORDER BY SUM(OL.Onum) DESC )
  AS desctop5(Cno,Onum) --降序查询前5
					ORDER BY SUM(desctop5.Onum) ASC--将顺序反转为升序
)--查询结果为第2-5名客户代码、订购数量
SELECT C.Cname ,R.Cno,R.sumnum 
FROM Result R
LEFT JOIN Customer C ON C.Cno=R.Cno;

--T-SQL查询(4)用游标编程，求大连市的杂志在2023年的平均订购数量和总订购数量的功能，不能用COUNT、AVG和SUM函数
GO
DECLARE @num INT;--每个订单订购数
DECLARE @count INT;--订单数
DECLARE @aver FLOAT;--平均数
DECLARE @totalnum INT;--总订购数
SET @num=0;
SET @count=0;
SET @totalnum=0;
DECLARE ordercursor CURSOR FOR
SELECT Onum
FROM OrderList OL
LEFT JOIN OrderH OH ON OL.Ono=OH.Ono 
LEFT JOIN Magazine M ON OL.Mno=M.Mno 
WHERE M.Mcity='大连'
AND YEAR(OH.Odate)=2023
OPEN ordercursor;
FETCH NEXT FROM ordercursor INTO @num;--将查询到的Onum赋值给@num
WHILE @@FETCH_STATUS = 0--循环条件
BEGIN 
	SET @totalnum=@totalnum+@num;
	SET @count=@count+1;
	FETCH NEXT FROM ordercursor INTO @num;	--获取下一行数据
END;
CLOSE ordercursor;
DEALLOCATE ordercursor;
SET @aver=CAST(@totalnum AS FLOAT) / CAST(@count AS FLOAT);
PRINT '大连市的杂志在2023年的平均订购数量 ' + CAST(@aver AS NVARCHAR);
PRINT '大连市的杂志在2023年的总订购数量 ' + CAST(@totalnum AS NVARCHAR);


--查询大连市的杂志在2023年的总订购数量
GO
SELECT SUM(Onum) AS  '大连市的杂志在2023年的总订购数量 '
FROM OrderList OL
LEFT JOIN OrderH OH ON OL.Ono=OH.Ono 
LEFT JOIN Magazine M ON OL.Mno=M.Mno 
WHERE M.Mcity='大连'
AND YEAR(OH.Odate)=2023
--查询大连市的杂志在2023年的总订购数量
SELECT COUNT(DISTINCT OL.Ono) AS  '大连市的杂志在2023年的订单数 '
FROM OrderList OL
LEFT JOIN OrderH OH ON OL.Ono=OH.Ono 
LEFT JOIN Magazine M ON OL.Mno=M.Mno 
WHERE M.Mcity='大连'
AND YEAR(OH.Odate)=2023;

--（1）设计存储过程pGetMoney，实现统计某年份给定客户类别的订购金额合计的功能，输入参数是统计年份和客户类别，输出参数是订购金额合计。
GO
CREATE PROCEDURE 
pGetMoney @year INT,
@type CHAR(20),
@result INT OUTPUT  --必须添加一个输出参数 @result INT OUTPUT来返回结果
	AS 
		SELECT @result = SUM(OrderList.Omoney)
		FROM OrderList
		LEFT JOIN OrderH ON  OrderList.Ono=OrderH.Ono  
		LEFT JOIN Customer ON OrderH.Cno=Customer.Cno
		WHERE YEAR(OrderH.Odate)=@year AND Customer.Ctype=@type;

--DROP PROCEDURE pGetMoney; 删除存储过程

--编写一段T-SQL程序调用存储过程pGetMoney，输出2023年客户类别为’企业单位’的订购金额合计。要求：调用语句的所有实参均使用局部变量，而且有输出语句
GO
DECLARE @year INT=2023;
DECLARE @type CHAR(20)= '企业单位';
DECLARE @result INT;
EXECUTE pGetMoney @year ,@type,@result OUTPUT;
PRINT '2023年客户类别为企业单位的订购金额合计: ' + CAST (@result AS NVARCHAR)+  ' $';



--设计自定义函数fGetProfit，实现统计某年份给定杂志类别的盈利金额合计的功能，输入参数是统计年份和杂志类别，输出参数是盈利金额合计
GO
CREATE FUNCTION fGetProfit (  @year INT , @type CHAR(20) ) RETURNS INT
	AS
	BEGIN 
		DECLARE @totalmoney INT
		SELECT @totalmoney = SUM(OrderList.Oprofit)
		FROM OrderList
		LEFT JOIN OrderH ON  OrderList.Ono=OrderH.Ono  
		LEFT JOIN Magazine ON OrderList.Mno=Magazine.Mno
		WHERE YEAR(OrderH.Odate)=@year AND Magazine.Mtype=@type
		RETURN @totalmoney
	END;

--DROP FUNCTION fGetProfit; 删除自定义函数

--编写一段T-SQL程序调用函数fGetProfit，输出2023年杂志类别为’科技类’的盈利金额合计。要求：调用语句的所有实参均使用局部变量，而且有输出语句
GO			
DECLARE @temp INT = dbo.fGetProfit(2023,'科技类')
PRINT '2023年杂志类别为’科技类’的盈利金额合计: ' + CAST (@temp AS NVARCHAR)+  ' $';

-- 在调用函数时候必须声明框架名  dbo.

--为杂志订购情况明细表OrderList定义一个【AFTER】触发器tr_after_OrderList，每插入一条订购情况明细记录（订单编号Ono，杂志代码Mno，订购数量Onum），
--自动根据杂志代码从杂志表获取该杂志的进货单价Miprice、订购单价Moprice，计算其订购金额Omoney和盈利金额Oprofit，
--同时自动计算订购情况主表OrderH的订单货款金额合计OMsum和订单盈利金额合计OPsum。
--其中，订购情况明细表OrderList的订购金额=订购单价×订购数量，盈利金额=（订购单价-进货单价）×订购数量
GO
CREATE TRIGGER tr_after_OrderList
	ON OrderList AFTER INSERT 
	AS
	BEGIN
		UPDATE OL 
		SET OL.Miprice=M.Miprice ,
		    OL.Moprice=M.Moprice ,
			OL.Omoney=M.Moprice*OL.Onum ,
			OL.Oprofit=(M.Moprice-M.Miprice)*OL.Onum
		FROM OrderList OL ,Magazine M,inserted I
		--更新条件
		WHERE OL.Ono = I.Ono AND OL.Mno=M.Mno
		PRINT'AFTER触发器在表OrderList成功'
		--更新OrderH的订单货款金额合计OMsum和订单盈利金额合计OPsum
		UPDATE OH
		--需将内层查询的OrderList与外层OrderH绑定连接
		SET OH.OMsum =(SELECT SUM(OrderList.Omoney) FROM OrderList WHERE OrderList.Ono=OH.Ono  GROUP BY OrderList.Ono),
			OH.OPsum =(SELECT SUM(OrderList.Oprofit) FROM OrderList WHERE OrderList.Ono=OH.Ono GROUP BY OrderList.Ono)
		FROM OrderH OH ,inserted I
		WHERE OH.Ono=I.Ono
		PRINT'AFTER触发器在表OrderH成功'
	END

--为杂志订购情况明细表OrderList定义一个【AFTER】触发器tr_after_OrderList，每插入一条订购情况明细记录（订单编号Ono，杂志代码Mno，订购数量Onum），
--自动根据杂志代码从杂志表获取该杂志的进货单价Miprice、订购单价Moprice，计算其订购金额Omoney和盈利金额Oprofit，
--同时自动计算订购情况主表OrderH的订单货款金额合计OMsum和订单盈利金额合计OPsum。
--其中，订购情况明细表OrderList的订购金额=订购单价×订购数量，盈利金额=（订购单价-进货单价）×订购数量

GO
CREATE TRIGGER tr_instead_OrderList
ON OrderList INSTEAD OF INSERT --当尝试向OrderList表插入数据时，不会执行默认的插入操作，而是执行这个触发器中定义的操作
AS
BEGIN
    -- 插入新的OrderList记录，同时计算Omoney和Oprofit
    INSERT INTO OrderList (Ono, Mno, Onum, Miprice, Moprice, Omoney, Oprofit)
    SELECT I.Ono, I.Mno, I.Onum, M.Miprice, M.Moprice, M.Moprice * I.Onum, (M.Moprice - M.Miprice) * I.Onum
    FROM inserted I INNER JOIN Magazine M ON I.Mno = M.Mno
	PRINT'INSTEAD OF触发器在表OrderList成功';
    -- 更新OrderH的OMsum和OPsum
    UPDATE OH 
    SET OH.OMsum = (SELECT SUM(OL.Omoney) FROM OrderList OL WHERE OL.Ono = OH.Ono),
        OH.OPsum = (SELECT SUM(OL.Oprofit) FROM OrderList OL WHERE OL.Ono = OH.Ono)
    FROM OrderH OH INNER JOIN inserted I ON OH.Ono = I.Ono
	PRINT'INSTEAD OF触发器在表OrderH成功'
END;

