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


; #4

(define length
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else (+ 1 (length (cdr lst)))))))

(print (length nums))
(print (length chars))


; #5

(define reverse-aux
  (lambda (lst last)
    (cond
      ((null? lst) last)
      (else (reverse-aux (cdr lst) (cons (car lst) last))))))

(define reverse
  (lambda (lst)
    (reverse-aux lst '())))

(print (reverse nums))
(print (reverse chars))


; #6

(define palindrome-test '(0 1 2 3 4 3 2 1 0))

(define list-eq?
  (lambda (lhs rhs)
    (cond
      ((null? lhs) (null? rhs))
      ((eq? (car lhs) (car rhs)) (list-eq? (cdr lhs) (cdr rhs)))
      (else #f))))

(define palindrome?
  (lambda (lst)
    (cond
      ((list-eq? (reverse lst) lst) #t)
      (else #f))))

(print (palindrome? nums))
(print (palindrome? chars))
(print (palindrome? palindrome-test))


; #7

(define flatten
  (lambda (lst)
    (cond
      ((null? lst) '())
      ((list? (car lst)) (append (flatten (car lst)) (flatten (cdr lst))))
      (else (cons (car lst) (flatten (cdr lst)))))))

(print (flatten '(0 1 2 3 4 5 6)))
(print (flatten '((0 1) (2 (3 4)) 5 (6))))


; #8

(define compress
  (lambda (lst)
    (cond
      ((null? lst) '())
      ((null? (cdr lst)) lst)
      ((eq? (car lst) (cadr lst)) (compress (cdr lst)))
      (else (cons (car lst) (compress (cdr lst)))))))

(print (compress '()))
(print (compress '(1 1)))
(print (compress '(0 1 2 3 4 5 6)))
(print (compress '(0 0 0 0 1 1 2 2 2 2 2 3 3 3 4 4 4 5 6)))
