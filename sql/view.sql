-- 示例
CREATE VIEW IF NOT EXISTS result AS
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
