/* ------------------------------------------------------------------------ *
 * CRUD - Create
 * ------------------------------------------------------------------------ */

/* 插入数据。
 * <http://sqlite.org/lang_insert.html>
 */
INSERT OR IGNORE INTO 'table' (intc, realc, txtc) VALUES
  (0, 3., 'Alpha'),
  (1, 3.1, 'Beta'),
  (1, 3.14, 'Gamma'),
  (2, 3.142, 'Delta'),
  (3, 3.1416, 'Epsilon'),
  (5, 3.14159, 'Zeta'),
  (8, 3.141593, 'Eta'),
  (13, 3.1415927, 'Theta'),
  (21, 3.14159265, 'Iota'),
  (34, 3.141592654, 'Kappa'),
  (55, 3.1415926536, 'Lambda'),
  (89, 3.14159265359, 'Mu'),
  (144, 3.141592653590, 'Nu'),
  (233, 3.1415926535898, 'Xi'),
  (377, 3.14159265358979, 'Omicron'),
  (610, 3.141592653589793, 'Pi'),
  (987, 3.1415926535897932, 'Rho'),
  (1597, 3.14159265358979324, 'Sigma'),
  (2584, 3.141592653589793238, 'Tau'),
  (4181, 3.1415926535897932385, 'Upsilon'),
  (6765, 3.14159265358979323846, 'Phi'),
  (10946, 3.141592653589793238463, 'Chi'),
  (17711, 3.1415926535897932384626, 'Psi'),
  (28657, 3.14159265358979323846264, 'Omega');

-- 示例
INSERT INTO implementation (interfaceid, environmentid, operation)
  SELECT
    interface.id,
    environment.id,
    '操作'
  FROM
    interface, environment
  WHERE
    interface.brief = '描述' AND
    environment.description LIKE '环境';

/* ------------------------------------------------------------------------ *
 * CRUD - Read
 * ------------------------------------------------------------------------ */

/* 查询数据。
 * <http://sqlite.org/lang_select.html>
 */
SELECT *
FROM 'table';

-- 示例
SELECT
  interface.brief,
  interface.details,
  environment.description,
  implementation.operation
FROM
  interface, environment, implementation
WHERE
  interface.id = implementation.interfaceid AND
  environment.id = implementation.environmentid;


/* ------------------------------------------------------------------------ *
 * CRUD - Update
 * ------------------------------------------------------------------------ */

/* 修改数据。
 * <http://sqlite.org/lang_update.html>
 */
UPDATE OR IGNORE 'table'
SET intc = -1
WHERE intc = 1;

/* ------------------------------------------------------------------------ *
 * CRUD - Delete
 * ------------------------------------------------------------------------ */

/* 删除数据。
 * <http://sqlite.org/lang_delete.html>
 */
DELETE FROM 'table'
WHERE intc != 1;

/* 删除全部数据。
 */
DELETE FROM 'table';
