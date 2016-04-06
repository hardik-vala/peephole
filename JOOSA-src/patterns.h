/*
 * JOOS is Copyright (C) 1997 Laurie Hendren & Michael I. Schwartzbach
 *
 * Reproduction of all or part of this software is permitted for
 * educational or research use on condition that this copyright notice is
 * included in any copy. This software comes with no warranty of any
 * kind. In no event will the authors be liable for any damages resulting from
 * use of this software.
 *
 * email: hendren@cs.mcgill.ca, mis@brics.dk
 */

/* Handle dup'ing and then compare equals branching */
int simplify_dup_cmpeq(CODE **c)
{
  int x,y;
  if (is_dup(*c))
  {
    if (is_if_acmpeq(next(*c),&x))
    {
      return replace_modified(c,2, makeCODEgoto(x, NULL));
    }
    else if (is_if_icmpeq(next(*c),&y))
    {
      return replace_modified(c,2, makeCODEgoto(y, NULL));
    }
  }
  return 0;
}

/* load 1
 * load 1
 * ------->
 * load 1
 * dup
 */
int replace_double_load_with_dup(CODE **c)
{
  int x,y;
  if (is_iload(*c, &x) && is_iload(next(*c), &y)) {
    if (x == y)
    {
      CODE* n = next(*c);
      return replace(&n, 1, makeCODEdup(NULL));
    }
  }
  else if (is_aload(*c, &x) && is_aload(next(*c), &y))
  {
    if (x == y)
    {
      CODE* n = next(*c);
      return replace(&n, 1, makeCODEdup(NULL));
    }
  }
  return 0;
}

/* Delete nops because they do nothing */
int rm_nops(CODE **c)
{
  if (is_nop(*c))
  {
    return(kill_line(c));
  }
  return 0;
}

/* dup
 * istore
 * pop
 * ----->
 * istore x
 */
int simplify_istore(CODE **c)
{
  int x;
  if (is_dup(*c) && is_istore(next(*c), &x) && is_pop(next(next(*c)))) 
  {
    return replace(c,3,makeCODEistore(x,NULL));
  }
  return 0;
}

/* remove any sort of loads followed by pops
 */
int rm_redundant_loads(CODE **c)
{
  int x;
  if (is_iload(*c, &x) && is_pop(next(*c)))
  {
    CODE *n = next(*c);
    kill_line(&n);
    return kill_line(c);
  }
  return 0;
}

/* iload 1
 * istore 1
 * -------->
 * 
 */
 int rm_same_iload_istore(CODE **c)
 {
  int x,y;
  if (is_iload(*c,&x) && is_istore(next(*c),&y))
  {
    if (x==y)
    {
      CODE* n = next(*c);
      kill_line(&n);
      return(kill_line(c));
    }
  }
  return 0;
 }

 /* aload 1
 * astore 1
 * -------->
 * 
 */
 int rm_same_aload_astore(CODE **c)
 {
  int x,y;
  if (is_aload(*c,&x) && is_astore(next(*c),&y))
  {
    if (x==y)
    {
      CODE* n = next(*c);
      kill_line(&n);
      return(kill_line(c));
    }
  }
  return 0;
 }

/* iload x        iload x        iload x
 * ldc 0          ldc 1          ldc 2
 * imul           imul           imul
 * ------>        ------>        ------>
 * ldc 0          iload x        iload x
 *                               dup
 *                               iadd
 */

int simplify_multiplication_right(CODE **c)
{ int x,k;
  if (is_iload(*c,&x) &&
      is_ldc_int(next(*c),&k) &&
      is_imul(next(next(*c)))) {
     if (k==0) return replace(c,3,makeCODEldc_int(0,NULL));
     else if (k==1) return replace(c,3,makeCODEiload(x,NULL));
     else if (k==2) return replace(c,3,makeCODEiload(x,
                                       makeCODEdup(
                                       makeCODEiadd(NULL))));
     return 0;
  }
  return 0;
}

/* dup
 * astore x
 * pop
 * -------->
 * astore x
 */
int simplify_astore(CODE **c)
{ int x;
  if (is_dup(*c) &&
      is_astore(next(*c),&x) &&
      is_pop(next(next(*c)))) {
     return replace(c,3,makeCODEastore(x,NULL));
  }
  return 0;
}

/* iload x
 * ldc k   (0<=k<=127)
 * iadd
 * istore x
 * --------->
 * iinc x k
 */
int positive_increment(CODE **c)
{ int x,y,k;
  if (is_iload(*c,&x) &&
      is_ldc_int(next(*c),&k) &&
      is_iadd(next(next(*c))) &&
      is_istore(next(next(next(*c))),&y) &&
      x==y && 0<=k && k<=127) {
     return replace(c,4,makeCODEiinc(x,k,NULL));
  }
  return 0;
}

/* goto L1
 * ...
 * L1:
 * goto L2
 * ...
 * L2:
 * --------->
 * goto L2
 * ...
 * L1:    (reference count reduced by 1)
 * goto L2
 * ...
 * L2:    (reference count increased by 1)
 */
int simplify_goto_goto(CODE **c)
{ int l1,l2;
  if (is_goto(*c,&l1) && is_goto(next(destination(l1)),&l2) && l1>l2) {
     droplabel(l1);
     copylabel(l2);
     return replace(c,1,makeCODEgoto(l2,NULL));
  }
  return 0;
}

#define OPTS 10

OPTI optimization[OPTS] = { 
  simplify_dup_cmpeq,
  rm_same_aload_astore,
  rm_redundant_loads,
  rm_same_iload_istore,
  simplify_istore,
  rm_nops,
                            simplify_multiplication_right,
                            simplify_astore,
                            positive_increment,
                            simplify_goto_goto};
