; #14

(define dupli
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (append (list (car lst) (car lst)) (dupli (cdr lst)))))))

(print (dupli '(0 1 2 3 4 5)))


; #15

(define make-loop
  (lambda (elem count)
    (cond
      ((zero? count) '())
      (else (cons elem (make-loop elem (- count  1)))))))

(define repli
  (lambda (lst count)
    (cond
      ((null? lst) '())
      (else (append (make-loop (car lst) count) (repli (cdr lst) count))))))

(print (repli '(0 1 2 3 4 5) 3))


; #16

(define drop
  (lambda (lst count)
    (cond
      ((null? lst) '())
      ((eq? count 1) (cdr lst))
      (else (cons (car lst) (drop (cdr lst) (- count 1)))))))

(print (drop '(0 1 2 3 4 5 6) 3))
