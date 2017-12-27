package bit.minisys.minicc.parser;








public class Table
{
  String[] PROGRAM = { "FUNCTIONS" };
  String[] FUNCTIONS = { "FUNCTION FUNLIST" };
  String[] FUNLIST = { "FUNCTIONS", "NULL" };
  
  String[] FUNCTION = { "TYPE TKN_ID TKN_LP ARGS TKN_RP FUNC_BODY" };
  String[] ARGS = { "FARGS ALIST", "NULL" };
  String[] FARGS = { "TYPE TKN_ID" };
  String[] ALIST = { "TKN_COMMA FARGS ALIST", "NULL" };
  
  String[] FUNC_BODY = { "TKN_LB STMTS TKN_RB" };
  String[] STMTS = { "STMT STMTS", "NULL" };
  String[] STMT = { "EXPR_STMT", "RET_STMT", "FOR_STMT", "IF_STMT" };
  
  String[] EXPR_STMT = { "EXPR TKN_SEMICOLON" };
  String[] EXPR = { "FACTOR FLIST", "EARGS" };
  String[] FACTOR = { "TKN_LP EXPR TKN_RP", "TKN_ID", "TKN_CONST_I" };
  String[] FLIST = { "TKN_ASN FACTOR FLIST", "TKN_PLUS FACTOR FLIST", "TKN_LESS FACTOR FLIST", "NULL" };
  String[] EARGS = { "FARGS EALIST", "NULL" };
  String[] EALIST = { "TKN_COMMA TKN_ID EALIST", "NULL" };
  
  String[] RET_STMT = { "TKN_KW_RET EXPR_STMT" };
  
  String[] FOR_STMT = { "TKN_FOR TKN_LP EXPR_STMT EXPR_STMT EXPR TKN_RP TKN_LB STMTS TKN_RB" };
  
  String[] IF_STMT = { "TKN_IF TKN_LP EXPR TKN_RP TKN_LB STMTS TKN_RB ELSEIF" };
  String[] ELSEIF = { "TKN_ELSE ILIST", "NULL" };
  String[] ILIST = { "IF_STMT", "TKN_LB STMTS TKN_RB" };
  
  String[] TYPE = { "TKN_INT", "TKN_FLOAT" };
  
  public Table() {}
}
