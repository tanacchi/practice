(define (range first last)
  (define (range-aux target end op)
    (cond
      ((eq? target (op end 1)) '())
      (else (cons target (range-aux (op target 1) end op)))))
  (cond
    ((< first last) (range-aux first last +))
    (else (range-aux first last -))))

(display (range 9 4))
(display (range 4 9))
