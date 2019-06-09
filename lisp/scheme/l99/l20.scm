(define (remove-at lst at)
  (define (remove-at-aux lst count buff)
    (cond
      ((null? lst) '())
      ((eq? count 1) (append (reverse buff) (cdr lst)))
      (else (remove-at-aux (cdr lst) (- count 1) (cons (car lst) buff)))))
  (remove-at-aux lst at '()))

(display (remove-at '(0 1 2 3 4 5 6 7) 3))
