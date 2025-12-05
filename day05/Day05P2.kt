data class Marker(val value: Long, val on: Boolean)

private fun toRange(line: String): List<Marker> {
  val (begin, end) = line.split("-").map { it.toLong() }
  return listOf(Marker(begin, true), Marker(end + 1, false))
}

fun main() {
  val rangeMarkers = 
      generateSequence(::readLine)
      .takeWhile { it.isNotEmpty() }
      .flatMap(::toRange)
      .sortedBy { it.value }
  var start: Long = -1 // will be immediately set on first loop iteration
  var onCount = 0
  var total = 0L
  for (m in rangeMarkers) {
    if (m.on) {
      ++onCount
      if (onCount == 1) {
        // starting a new range
        start = m.value
      }
    } else {
      --onCount
      check(onCount >= 0)
      if (onCount == 0) {
        // all open ranges have been closed
        total += (m.value - start)
      }
    }
  }
  println(total)


}
