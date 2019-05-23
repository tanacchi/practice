(define divisible?
  (lambda (target base)
    (cond
      ((eq? target base) #t)
      ((< target base) #f)
      ((> target base) (divisible? (- target base) base)))))


(define drop-aux
  (lambda (lst base count)
    (cond
      ((null? lst) '())
      ((divisible? count base) (drop-aux (cdr lst) base (+ count 1)))
      (else (cons (car lst) (drop-aux (cdr lst) base (+ count 1)))))))


(define drop
  (lambda (lst base)
    (drop-aux lst base 1)))


(print (drop '(0 1 2 3 4 5 6 7 8 9) 3))
