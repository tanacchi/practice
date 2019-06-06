(define slice-aux
  (lambda (lst head tail buff)
    (cond
      ((null? lst) '())
      ((> head 1) (slice-aux (cdr lst) (- head 1) (- tail 1) buff))
      ((zero? tail) buff)
      (else (append buff (list (car lst)) (slice-aux (cdr lst) 0 (- tail 1) buff))))))

(define slice
  (lambda (lst head tail)
    (cond
      ((> head tail) '())
      (else (slice-aux lst head tail '())))))

(print (slice '(0 1 2 3) 1 3))
