(define (remove-at lst count)
  (cond
    ((null? lst) '())
    ((eq? count 1) (cdr lst))
    (else (cons (car lst) (remove-at (cdr lst) (- count 1))))))

(display (remove-at '(0 1 2 3 4 5 6 7) 3))
