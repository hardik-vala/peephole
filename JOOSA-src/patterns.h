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

/*****************************************************
 * Patterns                                          *
 *                                                   *
 * Group 05: Ethan Macdonald, Teng Long, Hardik Vala *
 *****************************************************/


/*
 * branch L1:
 * ...
 * L1:
 * L2:
 * --------->
 * branch L2:
 * ...
 * L1:
 * L2:
 */
/* TODO: Doesn't do anything. Test again */
int branch_to_last_label(CODE **c)
{ int l1, l2;

  /* goto */
  if (is_goto(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEgoto(l2, NULL));
  }

  /* ifeq */
  if (is_ifeq(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEifeq(l2, NULL));
  }

  /* ifneq */
  if (is_ifne(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEifne(l2, NULL));
  }

  /* ifnull */
  if (is_ifnull(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEifnull(l2, NULL));
  }

  /* ifnonnull */
  if (is_ifnonnull(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEifnonnull(l2, NULL));
  }

  /* if_icmpeq */
  if (is_if_icmpeq(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmpeq(l2, NULL));
  }

  /* if_icmpneq */
  if (is_if_icmpne(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmpne(l2, NULL));
  }

  /* if_icmpgt */
  if (is_if_icmpgt(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmpgt(l2, NULL));
  }

  /* if_icmplt */
  if (is_if_icmplt(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmplt(l2, NULL));
  }

  /* if_icmpge */
  if (is_if_icmpge(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmpge(l2, NULL));
  }

  /* if_icmple */
  if (is_if_icmple(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_icmple(l2, NULL));
  }

  /* if_acmpeq */
  if (is_if_acmpeq(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_acmpeq(l2, NULL));
  }

  /* if_acmpneq */
  if (is_if_acmpne(*c, &l1) && is_label(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 1, makeCODEif_acmpne(l2, NULL));
  }

  return 0;
}

/*
 * branch1 L1         (branch1: ifeq, ifneq, ifnull, ifnonnull, if_icmpeq,
 *                     ificmpneq, if_icmpgt, if_icmplt, if_icmpge, if_icmple,
 *                     if_acmpeq, or if_acmpneq) (NOT goto)
 *                    (L1: Unique)
 * goto L2
 * L1:
 * ldc x              (Integer or string)
 * --------->
 * branch2 L2         (branch2: Opposite of branch1)
 * ldc x
 */
int collapse_branch_goto(CODE **c)
{ int l1, l2, l3, x;
  char* s;

  /* ifeq, ldc integer */
  if (is_ifeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEifne(l2, makeCODEldc_int(x, NULL)));
  }

  /* ifneq, ldc integer */
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEifeq(l2, makeCODEldc_int(x, NULL)));
  }

  /* ifnull, ldc integer */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEifnonnull(l2, makeCODEldc_int(x, NULL)));
  }

  /* ifnonnull, ldc integer */
  if (is_ifnonnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEifnull(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmpeq, ldc integer */
  if (is_if_icmpeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmpne(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmpneq, ldc integer */
  if (is_if_icmpne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmpeq(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmpgt, ldc integer */
  if (is_if_icmpgt(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmple(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmplt, ldc integer */
  if (is_if_icmplt(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmpge(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmpge, ldc integer */
  if (is_if_icmpge(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmplt(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_icmple, ldc integer */
  if (is_if_icmple(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_icmpgt(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_acmpeq, ldc integer */
  if (is_if_acmpeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_acmpne(l2, makeCODEldc_int(x, NULL)));
  }

  /* if_acmpneq, ldc integer */
  if (is_if_acmpne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 3), &x)) {
    return replace(c, 4, makeCODEif_acmpeq(l2, makeCODEldc_int(x, NULL)));
  }

  /* ifeq, ldc string */
  if (is_ifeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEifne(l2, makeCODEldc_string(s, NULL)));
  }

  /* ifneq, ldc string */
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEifeq(l2, makeCODEldc_string(s, NULL)));
  }

  /* ifnull, ldc string */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEifnonnull(l2, makeCODEldc_string(s, NULL)));
  }

  /* ifnonnull, ldc string */
  if (is_ifnonnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEifnull(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmpeq, ldc string */
  if (is_if_icmpeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmpne(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmpneq, ldc string */
  if (is_if_icmpne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmpeq(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmpgt, ldc string */
  if (is_if_icmpgt(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmple(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmplt, ldc string */
  if (is_if_icmplt(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmpge(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmpge, ldc string */
  if (is_if_icmpge(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmplt(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_icmple, ldc string */
  if (is_if_icmple(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_icmpgt(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_acmpeq, ldc string */
  if (is_if_acmpeq(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_acmpne(l2, makeCODEldc_string(s, NULL)));
  }

  /* if_acmpneq, ldc string */
  if (is_if_acmpne(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_ldc_string(nextby(*c, 3), &s)) {
    return replace(c, 4, makeCODEif_acmpeq(l2, makeCODEldc_string(s, NULL)));
  }

  return 0;
}

/* 
 * branch1 L1         (branch1: ifeq, ifneq, ifnull, ifnonnull, if_icmpeq,
 *                     ificmpneq, if_icmpgt, if_icmplt, if_icmpge, if_icmple,
 *                     if_acmpeq, or if_acmpneq) (NOT goto)
 *                    (L1: Unique)
 * iconst_0
 * goto L2            (L2: Unique)
 * L1:
 * iconst_1
 * L2:
 * ifeq L3
 * --------->
 * branch2 L3         (branch2: ifneq, ifeq, ifnonnull, ifnull, if_icmpneq,
 *                     ificmpeq, if_icmple, if_icmpge, if_icmplt, if_icmpgt,
 *                     if_acmpneq, or if_acmpeq, respectively, depending on the
 *                     identity of branch1) (The opposite of branch1)
 */
int collapse_local_branching(CODE **c)
{ int l1, l2, l3, l4, l5, x1, x2;

  /* ifeq --> ifneq */
  if (is_ifeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEifne(l5, NULL));
  }

  /* ifneq --> ifeq */
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEifeq(l5, NULL));
  }

  /* ifnull --> ifnonnull */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEifnonnull(l5, NULL));
  }

  /* ifnonnull --> ifnull */
  if (is_ifnonnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEifnull(l5, NULL));
  }

  /* if_icmpeq --> if_icmpneq */
  if (is_if_icmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmpne(l5, NULL));
  }

  /* if_icmpneq --> if_icmpeq */
  if (is_if_icmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmpeq(l5, NULL));
  }

  /* if_icmpgt --> if_icmple */
  if (is_if_icmpgt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmple(l5, NULL));
  }

  /* if_icmplt --> if_icmpge */
  if (is_if_icmplt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmpge(l5, NULL));
  }

  /* if_icmpge --> if_icmplt */
  if (is_if_icmpge(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmplt(l5, NULL));
  }

  /* if_icmple --> if_icmpgt */
  if (is_if_icmple(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_icmpgt(l5, NULL));
  }

  /* if_acmpeq --> if_acmpneq */
  if (is_if_acmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_acmpne(l5, NULL));
  }

  /* if_acmpneq --> if_acmpeq */
  if (is_if_acmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_ifeq(nextby(*c, 6), &l5)) {
    return replace(c, 7, makeCODEif_acmpeq(l5, NULL));
  }

  return 0;
}

/* 
 * branch1 L1         (branch1: ifeq, ifneq, ifnull, ifnonnull, if_icmpeq,
 *                     ificmpneq, if_icmpgt, if_icmplt, if_icmpge, if_icmple,
 *                     if_acmpeq, or if_acmpneq) (NOT goto)
 *                    (L1: Unique)
 * iconst_0
 * goto L2            (L2: Unique)
 * L1:
 * iconst_1
 * L2:
 * dup
 * {ifeq, ifneq} L3
 * pop
 * --------->
 * branch2 L1         (If ifeq, then branch2 = branch1, otherwise branch2 is the
 *                     opposite)
 * ldc x              (x: 0 if ifeq, 1 otherwise)
 * goto L3
 * L1:
 */
int collapse_local_branching_with_dup(CODE **c)
{ int l1, l2, l3, l4, l5, x1, x2;
  
  /* ifeq, ifeq */
  if (is_ifeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifeq(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifeq, ifneq */
  if (is_ifeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifne(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifneq, ifeq */
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifne(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifneq, ifneq */
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifeq(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifnull, ifeq */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifnull(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifnull, ifneq */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifnonnull(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifnonnull, ifeq */
  if (is_ifnonnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifnonnull(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* ifnonnull, ifneq */
  if (is_ifnonnull(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEifnull(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpeq, ifeq */
  if (is_if_icmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpeq(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpeq, ifneq */
  if (is_if_icmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpne(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpneq, ifeq */
  if (is_if_icmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpne(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpneq, ifneq */
  if (is_if_icmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpeq(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpgt, ifeq */
  if (is_if_icmpgt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpgt(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpgt, ifneq */
  if (is_if_icmpgt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmple(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmplt, ifeq */
  if (is_if_icmplt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmplt(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmplt, ifneq */
  if (is_if_icmplt(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpge(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpge, ifeq */
  if (is_if_icmpge(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpge(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmpge, ifneq */
  if (is_if_icmpge(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmplt(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmple, ifeq */
  if (is_if_icmple(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmple(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_icmple, ifneq */
  if (is_if_icmple(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_icmpgt(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_acmpeq, ifeq */
  if (is_if_acmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_acmpeq(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_acmpeq, ifneq */
  if (is_if_acmpeq(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_acmpne(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_acmpneq, ifeq */
  if (is_if_acmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifeq(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_acmpne(l1,
        makeCODEldc_int(0,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  /* if_acmpneq, ifneq */
  if (is_if_acmpne(*c, &l1) && uniquelabel(l1) &&
      is_ldc_int(next(*c), &x1) && x1 == 0 &&
      is_goto(nextby(*c, 2), &l2) && uniquelabel(l2) &&
      is_label(nextby(*c, 3), &l3) && l3 == l1 &&
      is_ldc_int(nextby(*c, 4), &x2) && x2 == 1 &&
      is_label(nextby(*c, 5), &l4) && l4 == l2 &&
      is_dup(nextby(*c, 6)) &&
      is_ifne(nextby(*c, 7), &l5) &&
      is_pop(nextby(*c, 8))) {
    return replace(c, 9,
      makeCODEif_acmpeq(l1,
        makeCODEldc_int(1,
          makeCODEgoto(l5,
            makeCODElabel(l1, NULL)
          )
        )
      )
    );
  }

  return 0;
}

/*
 * L: (Dead)
 * --------->
 *
 */
int drop_dead_label(CODE **c)
{ int l;
  if (is_label(*c, &l) && deadlabel(l)) {
    return replace(c, 1, NULL);
  }

  return 0;
}

/* 
 * load k
 * load k
 * ------->
 * load k
 * dup
 */
/* TODO: Doesn't do anything. Test again. */
int simplify_double_load(CODE **c)
{ int k1, k2;

  /* iload */
  if (is_iload(*c, &k1) && is_iload(next(*c), &k2) && k1 == k2) {
    CODE* n = next(*c);
    return replace(&n, 1, makeCODEdup(NULL));
  }

  /* aload */
  if (is_aload(*c, &k1) && is_aload(next(*c), &k2) && k1 == k2) {
    CODE* n = next(*c);
    return replace(&n, 1, makeCODEdup(NULL));
  }

  return 0;
}

/*
 * ifne L1
 * ...
 * L1:
 * dup
 * ifne L2
 * --------->
 * ifne L2
 * ...
 * L1:
 * dup
 * ifne L2
 */
/* TODO: Doesn't do anything (Actually adds to the total code length). */
int simplify_chained_ifneqs(CODE **c)
{ int l1, l2;
  if (is_ifne(*c, &l1) && uniquelabel(l1) &&
      is_dup(next(destination(l1))) &&
      is_ifne(nextby(destination(l1), 2), &l2)) {
    return replace(c, 1, makeCODEifne(l2, NULL));
  }

  return 0;
}

/*
 * {iconst_0, iconst_1}
 * goto L1
 * ...
 * L1:
 * {ifeq, ifneq} L2
 * --------->
 * goto L2
 * ...
 * L1:
 * {ifeq, ifneq} L2
 */
int simplify_goto_if(CODE **c)
{ int x, l1, l2;
  
  /* iconst_0, ifeq */
  if (is_ldc_int(*c, &x) && x == 0 &&
      is_goto(next(*c), &l1) &&
      is_ifeq(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 2, makeCODEgoto(l2, NULL));
  }

  /* iconst_1, ifneq */
  if (is_ldc_int(*c, &x) && x == 1 &&
      is_goto(next(*c), &l1) &&
      is_ifne(next(destination(l1)), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 2, makeCODEgoto(l2, NULL));
  }

  return 0;
}

/*
 * {iconst_0, iconst_1}
 * goto L1
 * ...
 * L1:
 * dup
 * {ifeq, ifneq} L2
 * --------->
 * {iconst_0, iconst_1}
 * goto L2
 * ...
 * L1:
 * dup
 * {ifeq, ifneq} L2
 */
int simplify_goto_dup_if(CODE **c)
{ int x, l1, l2;
  
  /* iconst_0, ifeq */
  if (is_ldc_int(*c, &x) && x == 0 &&
      is_goto(next(*c), &l1) &&
      is_dup(next(destination(l1))) &&
      is_ifeq(nextby(destination(l1), 2), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 2, makeCODEldc_int(0, makeCODEgoto(l2, NULL)));
  }

  /* iconst_1, ifneq */
  if (is_ldc_int(*c, &x) && x == 1 &&
      is_goto(next(*c), &l1) &&
      is_dup(next(destination(l1))) &&
      is_ifne(nextby(destination(l1), 2), &l2)) {
    droplabel(l1);
    copylabel(l2);
    return replace(c, 2, makeCODEldc_int(1, makeCODEgoto(l2, NULL)));
  }

  return 0;
}

/*
 * iconst_0
 * if_icmpeq L
 * --------->
 * ifeq L
 */
int simplify_ificmpeq_zero(CODE **c)
{ int k, l;
  if (is_ldc_int(*c, &k) && k == 0 && is_if_icmpeq(next(*c), &l)) {
    return replace(c, 2, makeCODEifeq(l, NULL));
  }

  return 0;
}

/*
 * iconst_0
 * if_icmpneq L
 * --------->
 * ifneq L
 */
int simplify_ificmpne_zero(CODE **c)
{ int k, l;
  if (is_ldc_int(*c, &k) && k == 0 && is_if_icmpne(next(*c), &l)) {
    return replace(c, 2, makeCODEifne(l, NULL));
  }

  return 0;
}

/*
 * ifnull L1    (L1: Unique)
 * goto L2
 * L1:
 * pop
 * ldc x
 * L2:
 * --------->
 * ifnonnull L2
 * pop
 * ldc x        (Integer or string)
 * L2:
 */
int simplify_ifnull(CODE **c)
{ int l1, l2, l3, l4, x;
  char* s;

  /* ldc integer */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_pop(nextby(*c, 3)) &&
      is_ldc_int(nextby(*c, 4), &x) &&
      is_label(nextby(*c, 5), &l4) && l4 == l2) {
    return replace(c, 6,
      makeCODEifnonnull(l2,
        makeCODEpop(
          makeCODEldc_int(x,
            makeCODElabel(l2, NULL)
          )
        )
      )
    );
  }

  /* ldc string */
  if (is_ifnull(*c, &l1) && uniquelabel(l1) &&
      is_goto(next(*c), &l2) &&
      is_label(nextby(*c, 2), &l3) && l3 == l1 &&
      is_pop(nextby(*c, 3)) &&
      is_ldc_string(nextby(*c, 4), &s) &&
      is_label(nextby(*c, 5), &l4) && l4 == l2) {
    return replace(c, 6,
      makeCODEifnonnull(l2,
        makeCODEpop(
          makeCODEldc_string(s,
            makeCODElabel(l2, NULL)
          )
        )
      )
    );
  }

  return 0;
}

/*
 * new ...
 * dup
 * ldc x (?)             (Integer or string)
 * invokenonvirtual ...
 * aload k
 * swap
 * --------->
 * aload k
 * new ...
 * dup
 * ldc x (?)
 * invokenonvirtual ...
 */
int simplify_invokenonvirtual(CODE **c)
{ int k, x;
  char *arg1, *arg2, *s;

  /* No ldc */
  if (is_new(*c, &arg1) &&
      is_dup(next(*c)) &&
      is_invokenonvirtual(nextby(*c, 2), &arg2) &&
      is_aload(nextby(*c, 3), &k) &&
      is_swap(nextby(*c, 4))) {
    return replace(c, 5,
      makeCODEaload(k,
        makeCODEnew(arg1,
          makeCODEdup(
            makeCODEinvokenonvirtual(arg2, NULL)
          )
        )
      )
    );
  }

  /* With ldc (integer) */
  if (is_new(*c, &arg1) &&
      is_dup(next(*c)) &&
      is_ldc_int(nextby(*c, 2), &x) &&
      is_invokenonvirtual(nextby(*c, 3), &arg2) &&
      is_aload(nextby(*c, 4), &k) &&
      is_swap(nextby(*c, 5))) {
    return replace(c, 6,
      makeCODEaload(k,
        makeCODEnew(arg1,
          makeCODEdup(
            makeCODEldc_int(x,
              makeCODEinvokenonvirtual(arg2, NULL)
            )
          )
        )
      )
    );
  }

  /* With ldc (string) */
  if (is_new(*c, &arg1) &&
      is_dup(next(*c)) &&
      is_ldc_string(nextby(*c, 2), &s) &&
      is_invokenonvirtual(nextby(*c, 3), &arg2) &&
      is_aload(nextby(*c, 4), &k) &&
      is_swap(nextby(*c, 5))) {
    return replace(c, 6,
      makeCODEaload(k,
        makeCODEnew(arg1,
          makeCODEdup(
            makeCODEldc_string(s,
              makeCODEinvokenonvirtual(arg2, NULL)
            )
          )
        )
      )
    );
  }

  return 0;
}

/* 
 * ldc x        (Integer or string)
 * dup
 * ifnull L
 * --------->
 * ldc x
 */
int simplify_ldc_dup_ifnull(CODE **c)
{ int x, l;
  char* s;

  /* Integer */
  if (is_ldc_int(*c, &x) && is_dup(next(*c)) && is_ifnull(nextby(*c, 2), &l)) {
    droplabel(l);
    return replace(c, 3, makeCODEldc_int(x, NULL));
  }

  /* String */
  if (is_ldc_string(*c, &s) && is_dup(next(*c)) && is_ifnull(nextby(*c, 2), &l)) {
    droplabel(l);
    return replace(c, 3, makeCODEldc_string(s, NULL));
  }

  return 0;
}

/* 
 * dup
 * aload 0
 * swap
 * putfield arg
 * pop
 * --------->
 * aload 0
 * swap
 * putfield arg
 */
int simplify_putfield(CODE **c)
{ int x;
  char* arg;
  if (is_dup(*c) &&
      is_aload(next(*c), &x) && x == 0 &&
      is_swap(nextby(*c, 2)) &&
      is_putfield(nextby(*c, 3), &arg) &&
      is_pop(nextby(*c, 4))) {
    return replace(c, 5,
      makeCODEaload(x,
        makeCODEswap(
          makeCODEputfield(arg, NULL)
        )
      )
    );
  }

  return 0;
}

/*
 * ldc x      (Integer or string)
 * aload k
 * swap
 * --------->
 * aload k
 * ldc x
 *
 * iload k
 * ldc x
 * iadd
 * aload l
 * swap
 * --------->
 * aload l
 * iload k
 * ldc x
 * iadd
 *
 * new ...
 * dup
 * aload k
 * getfield ...
 * invokenonvirtual ...
 * aload k
 * swap
 * --------->
 * aload k
 * new ...
 * dup
 * aload k
 * getfield ...
 * invokenonvirtual ...
 */
int simplify_simple_swap(CODE **c)
{ int k, l, x;
  char *s, *arg1, *arg2, *arg3;

  /* 
   * ldc x      (Integer)
   * aload k
   * swap
   * --------->
   * aload k
   * ldc x
   */
  if (is_ldc_int(*c, &x) && is_aload(next(*c), &k) && is_swap(nextby(*c, 2))) {
    return replace(c, 3, makeCODEaload(k, makeCODEldc_int(x, NULL)));
  }

  /* 
   * ldc x      (String)
   * aload k
   * swap
   * --------->
   * aload k
   * ldc x
   */
  if (is_ldc_string(*c, &s) && is_aload(next(*c), &k) && is_swap(nextby(*c, 2))) {
    return replace(c, 3, makeCODEaload(k, makeCODEldc_string(s, NULL)));
  }

  /* 
   * iload k
   * ldc x
   * iadd
   * aload l
   * swap
   * --------->
   * aload l
   * iload k
   * ldc x
   * iadd
   */
  if (is_iload(*c, &k) &&
      is_ldc_int(next(*c), &x) &&
      is_iadd(nextby(*c, 2)) &&
      is_aload(nextby(*c, 3), &l) &&
      is_swap(nextby(*c, 4))) {
    return replace(c, 5,
      makeCODEaload(l,
        makeCODEiload(k,
          makeCODEldc_int(x,
            makeCODEiadd(NULL)
          )
        )
      )
    );
  }

  /*
   * new ...
   * dup
   * aload k
   * getfield ...
   * invokenonvirtual ...
   * aload k
   * swap
   * --------->
   * aload k
   * new ...
   * dup
   * aload k
   * getfield ...
   * invokenonvirtual ...
   */
  if (is_new(*c, &arg1) &&
      is_dup(next(*c)) &&
      is_aload(nextby(*c, 2), &k) &&
      is_getfield(nextby(*c, 3), &arg2) &&
      is_invokenonvirtual(nextby(*c, 4), &arg3) &&
      is_aload(nextby(*c, 5), &l) && l == k &&
      is_swap(nextby(*c, 6))) {
    return replace(c, 7,
      makeCODEaload(k,
        makeCODEnew(arg1,
          makeCODEdup(
            makeCODEaload(k,
              makeCODEgetfield(arg2,
                makeCODEinvokenonvirtual(arg3, NULL)
              )
            )
          )
        )
      )
    );
  }

  /*
   * aload k
   * getfield ...
   * aload k
   * swap
   * --------->
   * aload k
   * dup
   * getfield ...
   */
  if (is_aload(*c, &k) &&
      is_getfield(next(*c), &arg1) &&
      is_aload(nextby(*c, 2), &l) && l == k &&
      is_swap(nextby(*c, 3))) {
    return replace(c, 4,
      makeCODEaload(k,
        makeCODEdup(
          makeCODEgetfield(arg1, NULL)
        )
      )
    );
  }

  return 0;
}

/* 
 * store k
 * load k
 * --------->
 * dup
 * store k
 */
int simplify_store_load(CODE **c)
{ int k1, k2;

  /* istore, iload */
  if (is_istore(*c, &k1) && is_iload(next(*c), &k2) && k1 == k2) {
    return replace(c, 2, makeCODEdup(makeCODEistore(k1, NULL)));
  }

  /* astore, aload */
  if (is_astore(*c, &k1) && is_aload(next(*c), &k2) && k1 == k2) {
    return replace(c, 2, makeCODEdup(makeCODEastore(k1, NULL)));
  }

  return 0;
}

/*
 * goto L
 * (Non-label)
 * --------->
 * goto L
 */
int strip_after_goto(CODE **c)
{ int l1, l2;
  if (is_goto(*c, &l1) &&
      !is_label(next(*c), &l2)) {
    return replace(c, 2, makeCODEgoto(l1, NULL));
  }

  return 0;
}

/*
 * {return, areturn, ireturn}
 * ...
 * L:
 * --------->
 * {return, areturn, ireturn}
 * L:
 */
/* TODO: Generalize this pattern to handle any number of intervening
 * statements. */
int strip_after_return(CODE **c)
{ int l1, l2;
  /* return. */
  if (is_return(*c) &&
      !is_label(next(*c), &l1) &&
      is_label(nextby(*c, 2), &l2)) {
    return replace_modified(c, 3, makeCODEreturn(makeCODElabel(l2, NULL)));
  }

  /* areturn. */
  if (is_areturn(*c) &&
      !is_label(next(*c), &l1) &&
      is_label(nextby(*c, 2), &l2)) {
    return replace_modified(c, 3, makeCODEareturn(makeCODElabel(l2, NULL)));
  }

  /* ireturn. */
  if (is_ireturn(*c) &&
      !is_label(next(*c), &l1) &&
      is_label(nextby(*c, 2), &l2)) {
    return replace_modified(c, 3, makeCODEireturn(makeCODElabel(l2, NULL)));
  }

  return 0;
}

/*
 * goto L
 * L:
 * --------->
 * L:
 */
int strip_stupid_goto(CODE **c)
{ int l1, l2;
  if (is_goto(*c, &l1) &&
      is_label(next(*c), &l2) && l1 == l2) {
    return replace(c, 2, makeCODElabel(l1, NULL));
  }

  return 0;
}

/*
 * i?return
 * nop
 * -------->
 * i?return (Not areturn)
 */
int strip_nops_after_return(CODE **c)
{ if (is_return(*c) && is_nop(next(*c))) {
    return replace(c, 2, makeCODEreturn(NULL));
  }

  if (is_ireturn(*c) && is_nop(next(*c))) {
    return replace(c, 2, makeCODEireturn(NULL));
  }

  return 0;
}

int load_load_swap(CODE **c)
{
  int first, second;
  if (is_iload(*c, &first))
  {
    if (is_iload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3, makeCODEiload(second, makeCODEiload(first, NULL)));
      }
    }
    else if(is_aload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3,makeCODEaload(second, makeCODEiload(first, NULL)));
      }
    }
  }
  else if (is_aload(*c, &first))
  {
    if (is_iload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3, makeCODEiload(second, makeCODEaload(first, NULL)));
      }
    }
    else if(is_aload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3,makeCODEaload(second, makeCODEaload(first, NULL)));
      }
    }
  }
  if (is_iload(*c, &first))
  {
    if (is_iload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3, makeCODEiload(second, makeCODEiload(first, NULL)));
      }
    }
    else if(is_aload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3,makeCODEaload(second, makeCODEiload(first, NULL)));
      }
    }
  }
  else if (is_aload(*c, &first))
  {
    if (is_iload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3, makeCODEiload(second, makeCODEaload(first, NULL)));
      }
    }
    else if(is_aload(next(*c), &second))
    {
      if (is_swap(next(next(*c))))
      {
        return replace(c,3,makeCODEaload(second, makeCODEaload(first, NULL)));
      }
    }
  }
  return 0;
}

int aconst_null_dup_ifeq(CODE **c)
{
  int y;
  if (is_aconst_null(*c))
  {
    if (is_dup(next(*c)) && (is_if_acmpeq(next(next(*c)), &y) || is_if_icmpeq(next(next(*c)), &y)))
    {
      return replace(c, 3, makeCODEgoto(y, NULL));
    }
  }
  return 0;
}

/*
 * ldc 0
 * iload x
 * iadd
 * ------>
 * iload x
 */

int simplify_addition_left(CODE **c) {
    int x, k;
    if (is_ldc_int(*c, &k) && is_iload(next(*c), &x) && is_iadd(next(next(*c)))) {
        if (k == 0) {
            return replace(c, 3, makeCODEiload(x, NULL));
        }
        return 0;
    }
    return 0;
}

/*
 * iload x
 * ldc 0
 * iadd
 * ------>
 * iload x
 */

int simplify_addition_right(CODE **c) {
    int x, k;
    if (is_iload(*c, &x) && is_ldc_int(next(*c), &k) && is_iadd(next(next(*c)))) {
        if (k == 0) {
            return replace(c, 3, makeCODEiload(x, NULL));
        }
        return 0;
    }
    return 0;
}

/*
 * iload x
 * idc 0
 * isub
 * ------>
 * iload x
 */

int simpify_subtraction_right(CODE **c) {
    int x, k;
    if (is_iload(*c, &x) && is_ldc_int(next(*c), &k) && is_isub(next(next(*c)))) {
        if (k == 0) {
            return replace(c, 3, makeCODEiload(x, NULL));
        }
        return 0;
    }
    return 0;
}

/* ldc 0            ldc 1           ldc 2
 * iload x          iload x         iload x
 * imul             imul            imul
 * ------>          ------>         ------>
 * ldc 0            iload x         iload x
 *                                  dup
 *                                  iadd
 */

int simplify_multiplication_left(CODE **c) {
    int x, k;
    if (is_ldc_int(*c, &k) && is_iload(next(*c), &x) && is_imul(next(next(*c)))) {
        if (k == 0){
            return replace(c, 3, makeCODEldc_int(0, NULL));
        } else if (k == 1) {
            return replace(c, 3, makeCODEiload(x, NULL));
        } else if (k == 2) {
            return replace(c, 3, makeCODEiload(x, makeCODEdup(makeCODEiadd(NULL))));
        }
        return 0;
    }
    return 0;
}

/* iload x
 * ldc 1
 * idiv
 * ------>
 * iload x
 */

int simplify_division_right(CODE **c) {
    int x, k;
    if (is_iload(*c, &x) && is_ldc_int(next(*c), &k) && is_idiv(next(next(*c)))) {
        if (k == 1) {
            return replace(c, 3, makeCODEiload(x, NULL));
        }
        return 0;
    }
    return 0;
}

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

/* aload 0
 * .......
 * .......
 * .......
 * aload 0
 * .......
 * .......
 * .......
 * ------>
 * aload 0
 * dup
 * TODO: doesn't work
 */

int simplify_two_aload_0(CODE **c) {
    int x, y;
    char *arg_1, *arg_2, *arg_3, *arg_4, *arg_5, *arg_6;
    if (is_aload(*c, &x) && is_getfield(next(*c), &arg_1) &&
        is_ldc_string(next(next(*c)), &arg_2) && is_invokevirtual(next(next(next(*c))), &arg_3) &&
        is_aload(next(next(next(next(*c)))), &y) && is_getfield(next(next(next(next(next(*c))))), &arg_4) &&
        is_ldc_string(next(next(next(next(next(next(*c)))))), &arg_5) && is_invokevirtual(next(next(next(next(next(next(next(*c))))))), &arg_6)) {
        if (x == 0 && y == 0) {
            return replace(c, 8, makeCODEaload(x,
                                    makeCODEdup(
                                        makeCODEgetfield(arg_1,
                                        makeCODEldc_string(arg_2,
                                        makeCODEinvokevirtual(arg_3,
                                        makeCODEgetfield(arg_4,
                                        makeCODEldc_string(arg_5,
                                        makeCODEinvokevirtual(arg_6,
                                        NULL))))))
                                    )));
        }
        return 0;
    }
    return 0;
}


/*********************
 * LAURIE'S PATTERNS *
 **********************/


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


/* TODO: Sometimes lowering this number results in more optimization (Huh?)... */
#define OPTS 35

OPTI optimization[OPTS] = {
  /* Our patterns. */
  branch_to_last_label,
  collapse_branch_goto,
  collapse_local_branching,
  collapse_local_branching_with_dup,
  drop_dead_label,
  // simplify_chained_ifneqs,
  simplify_goto_if,
  simplify_goto_dup_if,
  simplify_ificmpeq_zero,
  simplify_ificmpne_zero,
  simplify_ifnull,
  simplify_invokenonvirtual,
  simplify_ldc_dup_ifnull,
  simplify_putfield,
  simplify_simple_swap,
  simplify_store_load,
  strip_after_goto,
  strip_after_return,
  strip_stupid_goto,
  load_load_swap,
  aconst_null_dup_ifeq,
  simplify_dup_cmpeq,
  strip_nops_after_return,
  simplify_addition_left,
  simplify_addition_right,
  simpify_subtraction_right,
  simplify_multiplication_left,
  simplify_division_right,
  rm_same_iload_istore,
  rm_same_aload_astore,
  simplify_dup_cmpeq,
  simplify_istore,
  /* Laurie's patterns. */
  positive_increment,
  simplify_astore,
  simplify_goto_goto,
  simplify_multiplication_right
};

/*
 * TODO: Figure out why this method of adding patterns doesn't work.
int init_patterns()
{
  ADD_PATTERN(simplify_multiplication_right);
  ADD_PATTERN(simplify_astore);
  ADD_PATTERN(positive_increment);
  ADD_PATTERN(simplify_goto_goto);
}
*/
