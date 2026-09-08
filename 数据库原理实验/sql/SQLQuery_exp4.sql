--实验四

--（1）INSERT基本语句（插入全部列的数据）
-- 插入一个新顾客的记录
INSERT INTO CUSTOMER (C_CUSTKEY, C_NAME, C_ADDRESS, C_NATIONKEY, C_PHONE, C_ACCTBAL, C_MKTSEGMENT, C_COMMENT)
VALUES ('NewCust123', 'New Customer', '123 New Street', '001', '1234567890', 1000.00, 'Segment', 'New customer comment');

-- 插入一条订单明细记录
INSERT INTO LINEITEM (L_ORDERKEY, L_PARTKEY, L_SUPPKEY, L_LINENUMBER, L_QUANTITY, L_EXTENDEDPRICE, L_DISCOUNT, L_TAX, L_RETURNFLAG, L_LINESTATUS, L_SHIPDATE, L_COMMITDATE, L_RECEIPTDATE, L_SHIPINSTRUCT, L_SHIPMODE, L_COMMENT)
VALUES ('NewOrder001', 'NewPart001', 'NewSupp001', '001', 10, 500.00, 0.05, 0.08, 'N', 'O', '2024-05-10', '2024-05-08', '2024-05-15', 'Ship in person', 'Air', 'New line item comment');


--（2）INSERT基本语句（插入部分列的数据，要求随机生成某些数字列或者字符列的数据）
-- 插入一条订单记录，随机生成数值字段
INSERT INTO ORDERS (O_ORDERKEY, O_CUSTKEY, O_ORDERSTATUS, O_TOTALPRICE, O_ORDERDATE, O_ORDERPRIORITY)
VALUES ('NewOrder002', 'NewCust456', 'P', ROUND(RAND() * 1000 + 500, 2), '2024-05-10', 'High');


--（3）UPDATE基本语句（修改所有记录的某些列的值）
-- 修改所有零件的零售价，使其价格上浮10%
UPDATE PART
SET P_RETAILPRICE = P_RETAILPRICE * 1.1;


--（4）UPDATE基本语句（修改部分记录的某些列的值）
-- 修改顾客张三的国籍
UPDATE CUSTOMER
SET C_NATIONKEY = '002'
WHERE C_NAME = '张三';


--（5）DELETE基本语句（删除所有记录）
-- 删除所有订单记录
DELETE FROM ORDERS;


--（6）DELETE基本语句（删除部分记录）
-- 删除2011年1月1日之前订单记录
DELETE FROM ORDERS
WHERE O_ORDERDATE < '2011-01-01';


--（7）INSERT批量插入语句（把一个查询结果插入到另外一个表中）
-- 创建一个顾客购物统计表
CREATE TABLE CustomerShoppingStats (
    C_CUSTKEY CHAR(10),
    TotalOrders INT,
    TotalPrice REAL,
    PRIMARY KEY (C_CUSTKEY)
);

-- 插入数据
INSERT INTO CustomerShoppingStats (C_CUSTKEY, TotalOrders, TotalPrice)
SELECT O_CUSTKEY, COUNT(*), SUM(O_TOTALPRICE)
FROM ORDERS
GROUP BY O_CUSTKEY;


--（8）INSERT批量插入语句（使某个表的数据量倍增）
-- 零件表的数据插入零件表中，多次重复执行，知道总记录数达到50万为止，记录下执行了多少次
-- 为了保证实体完整性约束，每次插入数据时，可以使用临时表来存储原始数据，然后插入新的数据并根据需要合并成一个新的表
-- 假设原始零件表为part，临时表为temp_part，每次插入10000条数据，执行插入语句后，再将temp_part表与part表合并

-- 创建临时表
CREATE TABLE temp_part AS SELECT * FROM PART WHERE 1 = 0;

-- 重复执行插入语句，直到总记录数达到50万
DECLARE @insertedRecords INT = 0;
DECLARE @targetRecords INT = 500000;

WHILE @insertedRecords < @targetRecords
BEGIN
    INSERT INTO temp_part (P_PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT)
    SELECT TOP 10000 P_PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT
    FROM PART;

    SET @insertedRecords = @insertedRecords + 10000;

    -- 合并临时表和原始表
    MERGE INTO PART AS target
    USING temp_part AS source
    ON target.P_PARTKEY = source.P_PARTKEY
    WHEN NOT MATCHED THEN
    INSERT (P_PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT)
    VALUES (source.P_PARTKEY, source.P_NAME, source.P_MFGR, source.P_BRAND, source.P_TYPE, source.P_SIZE, source.P_CONTAINER, source.P_RETAILPRICE, source.P_COMMENT);
END;

-- 删除临时表
DROP TABLE temp_part;


--（9）UPDATE语句使用嵌套子查询（利用一个表中的数据来判断是否修改另外一个表中的数据）
-- 修改顾客张三的订单明细记录中111号零件的折扣
UPDATE LINEITEM
SET L_DISCOUNT = 0.1
WHERE L_PARTKEY = '111'
AND L_ORDERKEY IN (
    SELECT O_ORDERKEY
    FROM ORDERS
    WHERE O_CUSTKEY = (
        SELECT C_CUSTKEY
        FROM CUSTOMER
        WHERE C_NAME = '张三'
    )
);


--（10）UPDATE语句使用嵌套子查询（利用一个表中的数据修改另外一个表中的数据）
-- 利用LINEITEM表中的详细信息修改对应订单中的totalprice
-- 利用LINEITEM表中的详细信息修改对应订单中的totalprice
UPDATE ORDERS
SET O_TOTALPRICE = (
    SELECT SUM(L_EXTENDEDPRICE * (1 - L_DISCOUNT))
    FROM LINEITEM
    WHERE LINEITEM.L_ORDERKEY = ORDERS.O_ORDERKEY
)
WHERE O_ORDERKEY IN (
    SELECT DISTINCT L_ORDERKEY
    FROM LINEITEM
);

-- 利用PARTSUPP 表中的供应价格来修改LINEITEM中的EXTENDEDPRICE
UPDATE LINEITEM
SET L_EXTENDEDPRICE = PS_SUPPLYCOST * L_QUANTITY * (1 - L_DISCOUNT)
FROM LINEITEM
JOIN PARTSUPP ON LINEITEM.L_PARTKEY = PARTSUPP.PS_PARTKEY AND LINEITEM.L_SUPPKEY = PARTSUPP.PS_SUPPKEY;



--（11）DELETE语句使用嵌套子查询（利用一个表中的数据来判断是否删除另外一个表中的数据）
-- 删除顾客张三的订单记录
DELETE FROM ORDERS
WHERE O_CUSTKEY = (
    SELECT C_CUSTKEY
    FROM CUSTOMER
    WHERE C_NAME = '张三'
);
