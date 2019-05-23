(define split-aux
  (lambda (lst count buff)
    (cond
      ((null? lst) '())
      ((zero? count) (cons (reverse buff) (list lst)))
      (else (split-aux (cdr lst) (- count 1) (cons (car lst) buff))))))

(define split
  (lambda (lst count)
    (split-aux lst count '())))

(print (split '(0 1 2 3 4 5) 3))
