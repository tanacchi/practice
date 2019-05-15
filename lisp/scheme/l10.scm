(define nums '(0 1 2 3 4 5))
(define chars '("a" "b" "c" "d" "e" "f"))


; #1

(define last
  (lambda (lst)
    (cond
      ((null? lst) '())
      ((null? (cdr lst)) lst)
      (else (last (cdr lst))))))

(print (last nums))
(print (last chars))


; #2

(define last2
  (lambda (lst)
    (cond
      ((null? lst) '())
      ((null? (cdr lst)) lst)
      ((null? (cddr lst)) lst)
      (else (last2 (cdr lst))))))

(print (last2 nums))
(print (last2 chars))


; #3

(define element-at
  (lambda (lst count)
    (cond
      ((null? lst) '())
      ((eq? count 1) (car lst))
      (else (element-at (cdr lst) (- count 1))))))

(print (element-at nums 3))
(print (element-at chars 3))
