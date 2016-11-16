/* 新建表。
 * <http://sqlite.org/lang_createtable.html>
 */
CREATE TABLE IF NOT EXISTS "table" (
  id    INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  intc  INTEGER,
  realc REAL,
  txtc  TEXT,
  blobc BLOB
);

/* 删除表。
 * <http://sqlite.org/lang_droptable.html>
 */
DROP TABLE IF EXISTS "table";
